//
//  ISSSelector.m
//  Part of InterfaCSS - http://www.github.com/tolo/InterfaCSS
//
//  Created by Tobias Löfstrand on 2012-02-22.
//  Copyright (c) 2012 Leafnode AB.
//  License: MIT (http://www.github.com/tolo/InterfaCSS/LICENSE)
//

#import "ISSSelector.h"

#import "InterfaCSS.h"
#import "NSString+ISSStringAdditions.h"
#import "NSObject+ISSLogSupport.h"
#import "ISSPseudoClass.h"
#import "ISSUIElementDetails.h"
#import "ISSPropertyRegistry.h"

@implementation ISSSelector {
    BOOL _wildcardType;
}

#pragma mark - ISSelector interface

- (instancetype) initWithType:(Class)type wildcardType:(BOOL)wildcardType elementId:(NSString*)elementId styleClass:(NSString*)styleClass pseudoClasses:(NSArray*)pseudoClasses {
    self = [super init];
    if (self) {
        _wildcardType = wildcardType;
        _type = type;
        _elementId = elementId;
        _styleClass = [styleClass lowercaseString];
        if( pseudoClasses.count == 0 ) pseudoClasses = nil;
        _pseudoClasses = pseudoClasses;
    }
    return self;
};

+ (instancetype) selectorWithType:(NSString*)type elementId:(NSString*)elementId pseudoClasses:(NSArray*)pseudoClasses {
    return [self selectorWithType:type elementId:elementId styleClass:nil pseudoClasses:pseudoClasses];
}

+ (instancetype) selectorWithType:(NSString*)type styleClass:(NSString*)styleClass pseudoClasses:(NSArray*)pseudoClasses {
    return [self selectorWithType:type elementId:nil styleClass:styleClass pseudoClasses:pseudoClasses];
}

+ (instancetype) selectorWithType:(NSString*)type elementId:(NSString*)elementId styleClass:(NSString*)styleClass pseudoClasses:(NSArray*)pseudoClasses {
    Class typeClass = nil;
    BOOL wildcardType = NO;

    if( [type iss_hasData] ) {
        if( [type isEqualToString:@"*"] ) wildcardType = YES;
        else {
            type = [type lowercaseString];
            if( ![type hasPrefix:@"ui"] ) type = [@"ui" stringByAppendingString:type];
            ISSPropertyRegistry* registry = [InterfaCSS sharedInstance].propertyRegistry;
            typeClass = [registry canonicalTypeClassForType:type];
        }
    }

    if( typeClass || wildcardType || elementId || styleClass ) {
        return [[self alloc] initWithType:typeClass wildcardType:wildcardType elementId:elementId styleClass:styleClass pseudoClasses:pseudoClasses];
    } else if( [type iss_hasData] ) {
        if( [InterfaCSS interfaCSS].useLenientSelectorParsing ) {
            ISSLogWarning(@"Unrecognized type: %@ - using type as style class instead", type);
            return [[self alloc] initWithType:nil wildcardType:NO elementId:nil styleClass:type pseudoClasses:pseudoClasses];
        } else {
            ISSLogWarning(@"Unrecognized type: %@", type);
        }
    }  else {
        ISSLogWarning(@"Invalid selector - type and style class missing!");
    }
    return nil;
}

- (instancetype) copyWithZone:(NSZone*)zone {
    return [[(id)self.class allocWithZone:zone] initWithType:_type wildcardType:_wildcardType elementId:self.elementId styleClass:self.styleClass pseudoClasses:self.pseudoClasses];
}

- (BOOL) matchesElement:(ISSUIElementDetails*)elementDetails ignoringPseudoClasses:(BOOL)ignorePseudoClasses {
    // TYPE
    BOOL match = !self.type || _wildcardType;
    if( !match ) {
        match = elementDetails.canonicalType == self.type;
    }
    
    // ELEMENT ID
    if( match && self.elementId ) {
        match = [elementDetails.elementId iss_isEqualIgnoreCase:self.elementId];
    }
    
    // STYLE CLASS
    if( match && self.styleClass ) {
        match = [elementDetails.styleClasses containsObject:self.styleClass];
    }

    // PSEUDO CLASS
    if( !ignorePseudoClasses && match && self.pseudoClasses.count ) {
        for(ISSPseudoClass* pseudoClass in self.pseudoClasses) {
            match = [pseudoClass matchesElement:elementDetails];
            if( !match ) break;
        }
    }

    return match;
}

- (NSString*) displayDescription {
    ISSPropertyRegistry* registry = [InterfaCSS sharedInstance].propertyRegistry;

    NSString* typeString = _type ? [registry canonicalTypeForViewClass:_type] : @"";
    if( !_type && _wildcardType ) typeString = @"*";

    NSString* idString = @"";
    if( _elementId ) {
        idString = [NSString stringWithFormat:@"#%@", _elementId];
    }

    NSString* classString = @"";
    if( _styleClass ) {
        classString = [NSString stringWithFormat:@".%@", _styleClass];
    }

    NSString* pseudoClassSuffix = @"";
    if( self.pseudoClasses.count > 0 ) {
        for(ISSPseudoClass* pseudoClass in self.pseudoClasses) {
            pseudoClassSuffix = [pseudoClassSuffix stringByAppendingFormat:@":%@", pseudoClass.displayDescription];
        }
    }

//    return [NSString stringWithFormat:@"%@%@%@%@", typeString, idString, classString, pseudoClassSuffix];

    if ( typeString && _styleClass ) return [NSString stringWithFormat:@"%@%@.%@%@", typeString, idString, _styleClass, pseudoClassSuffix];
    else if ( typeString ) return [NSString stringWithFormat:@"%@%@%@", typeString, idString, pseudoClassSuffix];
    else return [NSString stringWithFormat:@"%@.%@%@", idString, _styleClass, pseudoClassSuffix];
}


#pragma mark - NSObject overrides

- (NSString*) description {
    return [NSString stringWithFormat:@"Selector(%@)", self.displayDescription];
}

- (BOOL) isEqual:(id)object {
    if( object == self ) return YES;
    else if ( [object isKindOfClass:ISSSelector.class] ) {
        ISSSelector* other = (ISSSelector*)object;
        return _wildcardType == other->_wildcardType && self.type == other.type &&
            [NSString iss_string:self.styleClass isEqualToString:other.styleClass] &&
            self.pseudoClasses == other.pseudoClasses ? YES : [self.pseudoClasses isEqual:other.pseudoClasses];
    } else return NO;
}

- (NSUInteger) hash {
    return 31u*31u * [self.type hash] + 31*[self.styleClass hash] + [self.pseudoClasses hash] + (_wildcardType ? 1 : 0);
}

@end
