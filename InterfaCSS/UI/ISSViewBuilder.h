//
//  ISSViewBuilder.h
//  Part of InterfaCSS - http://www.github.com/tolo/InterfaCSS
//
//  Created by Tobias Löfstrand on 2012-12-07.
//  Copyright (c) 2012 Leafnode AB.
//  License: MIT (http://www.github.com/tolo/InterfaCSS/LICENSE)
//

#import "ISSRootView.h" // Import this here to avoid users having to import this file as well when using methods like rootViewWithStyle...

#ifdef ISS_VIEW_BUILDER_SHORTHAND_ENABLED
#define ISSBuildRoot ISSViewBuilder rootViewWithStyle
#define ISSBuildView ISSViewBuilder viewWithStyle
#define ISSBuildCollectionView ISSViewBuilder collectionViewWithStyle
#define ISSBuildImageView ISSViewBuilder imageViewWithStyle
#define ISSBuildScrollView ISSViewBuilder scrollViewWithStyle
#define ISSBuildTableView ISSViewBuilder tableViewWithStyle
#define ISSBuildWebView ISSViewBuilder webViewWithStyle

#define ISSBuildActivityIndicator ISSViewBuilder activityIndicatorViewWithStyle
#define ISSBuildButton ISSViewBuilder buttonWithStyle
#define ISSBuildLabel ISSViewBuilder labelWithStyle
#define ISSBuildProgressView ISSViewBuilder progressViewWithStyle
#define ISSBuildSlider ISSViewBuilder sliderWithStyle
#define ISSBuildStepper ISSViewBuilder stepperWithStyle
#define ISSBuildSwitch ISSViewBuilder switchWithStyle
#define ISSBuildTextField ISSViewBuilder textFieldWithStyle
#define ISSBuildTextView ISSViewBuilder textViewWithStyle
#define ISSBuildTableViewCell ISSViewBuilder tableViewCellWithStyle

#define ISSEndContainer ]; }];
#define ISSEndRoot ISSEndContainer );

#define beginSubViews andSubViews:^{ return @[
#define endSubViews ]; }

#endif

typedef NSArray* (^SubViewBlock)();

/**
 * Factory class that enables building of view hierarchies in a concise and convenient way. Note that all the methods of this class support setting multiple
 * style classes in the `styleClassName` parameter, by separating them with a space.
 *
 * To enable the use of a shorthand syntax, define the macro `ISS_VIEW_BUILDER_SHORTHAND_ENABLED`.
 */
@interface ISSViewBuilder : NSObject


/**
 * Sets up the specified view by adding the specified view class(es) to it.
 */
+ (id) setupView:(UIView*)theView withStyleClass:(NSString*)styleClassName;
+ (id) setupView:(UIView*)theView withId:(NSString*)elementId andStyleClass:(NSString*)styleClassName;

/**
 * Sets up the specified view by adding the specified view class(es) and subviews, via a `SubViewBlock`.
 */
+ (id) setupView:(UIView*)theView withStyleClass:(NSString*)styleClassName andSubViews:(SubViewBlock)subViewBlock;
+ (id) setupView:(UIView*)theView withId:(NSString*)elementId andStyleClass:(NSString*)styleClassName andSubViews:(SubViewBlock)subViewBlock;


/**
 * Creates a view of class ISSRootView, intended to serve as the root view of a view controller.
 */
+ (ISSRootView*) rootViewWithStyle:(NSString*)styleClass;
+ (ISSRootView*) rootViewWithId:(NSString*)elementId;

/**
 * Creates a view of class ISSRootView, intended to serve as the root view of a view controller. Adds the subviews from the specified `SubViewBlock`.
 */
+ (ISSRootView*) rootViewWithStyle:(NSString*)styleClass andSubViews:(SubViewBlock)subViewBlock;
+ (ISSRootView*) rootViewWithId:(NSString*)elementId andSubViews:(SubViewBlock)subViewBlock;

/**
 * Creates a view of class ISSRootView, intended to serve as the root view of a view controller. If `owner` is specified, this method will attempt to auto populate 
 * properties for any views with an element id, created via the `SubViewBlock`.
 */
+ (ISSRootView*) rootViewWithStyle:(NSString*)styleClass withOwner:(id)owner andSubViews:(SubViewBlock)subViewBlock;
+ (ISSRootView*) rootViewWithId:(NSString*)elementId withOwner:(id)owner andSubViews:(SubViewBlock)subViewBlock;

/**
 * Creates a view of class ISSRootView, intended to serve as the root view of a view controller. If `owner` is specified, this method will attempt to auto populate
 * properties for any views with an element id, created via the `SubViewBlock`.
 */
+ (ISSRootView*) rootViewWithId:(NSString*)elementId andStyleClass:(NSString*)styleClass withOwner:(id)owner andSubViews:(SubViewBlock)subViewBlock;


/**
 * Loads a view hierarchy from the specified view definition XML file in the main bundle. Specifying a value for the `fileOwner` will enable setting
 * properties identified in the file.
 */
+ (ISSRootView*) loadViewHierarchyFromMainBundleFile:(NSString*)fileName withFileOwner:(id)fileOwner;

/**
 * Loads a view hierarchy from the specified view definition XML file in the local file system. Specifying a value for the `fileOwner` will enable setting
 * properties identified in the file.
 */
+ (ISSRootView*) loadViewHierarchyFromFile:(NSString*)fileName fileOwner:(id)fileOwner;


/**
 * Builds a `UIView` with the specified style class.
 */
+ (UIView*) viewWithStyle:(NSString*)styleClass;
+ (UIView*) viewWithId:(NSString*)elementId;

/**
 * Builds a `UIView` with the specified style class and adds the subviews from the specified `SubViewBlock`.
 */
+ (UIView*) viewWithStyle:(NSString*)styleClass andSubViews:(SubViewBlock)subViewBlock;
+ (UIView*) viewWithId:(NSString*)elementId andSubViews:(SubViewBlock)subViewBlock;

/**
 * Builds a view of the specified implementation class and style class.
 */
+ (UIView*) viewOfClass:(Class)clazz withStyle:(NSString*)styleClass;
+ (UIView*) viewOfClass:(Class)clazz withId:(NSString*)elementId;

/**
 * Builds a view of the specified implementation class and style class, and adds the subviews from the specified `SubViewBlock`.
 */
+ (UIView*) viewOfClass:(Class)clazz withStyle:(NSString*)styleClass andSubViews:(SubViewBlock)subViewBlock;
+ (UIView*) viewOfClass:(Class)clazz withId:(NSString*)elementId andStyle:(NSString*)styleClass andSubViews:(SubViewBlock)subViewBlock;


/**
 * Builds a `UICollectionView` with the specified style class.
 */
+ (UICollectionView*) collectionViewWithStyle:(NSString*)styleClass;
+ (UICollectionView*) collectionViewWithId:(NSString*)elementId;

/**
 * Builds a `UICollectionView` with the specified style class and adds the subviews from the specified `SubViewBlock`.
 */
+ (UICollectionView*) collectionViewWithStyle:(NSString*)styleClass andSubViews:(SubViewBlock)subViewBlock;

/**
 * Builds a `UICollectionView` with the specified implementation class and style class, and adds the subviews from the specified `SubViewBlock`.
 */
+ (UICollectionView*) collectionViewOfClass:(Class)clazz withStyle:(NSString*)styleClass andSubViews:(SubViewBlock)subViewBlock;

/**
 * Builds a `UICollectionView` with the specified implementation class, collection view layout class and style class, and adds the subviews from the specified `SubViewBlock`.
 */
+ (UICollectionView*) collectionViewOfClass:(Class)clazz collectionViewLayoutClass:(Class)collectionViewLayoutClass withStyle:(NSString*)styleClass andSubViews:(SubViewBlock)subViewBlock;
+ (UICollectionView*) collectionViewOfClass:(Class)clazz collectionViewLayoutClass:(Class)collectionViewLayoutClass withId:(NSString*)elementId andStyle:(NSString*)styleClass andSubViews:(SubViewBlock)subViewBlock;


/**
 * Builds a `UIImageView` with the specified style class.
 */
+ (UIImageView*) imageViewWithStyle:(NSString*)styleClass;
+ (UIImageView*) imageViewWithWithId:(NSString*)elementId;

/**
 * Builds a `UIImageView` with the specified style class and adds the subviews from the specified `SubViewBlock`.
 */
+ (UIImageView*) imageViewWithStyle:(NSString*)styleClass andSubViews:(SubViewBlock)subViewBlock;
+ (UIImageView*) imageViewWithId:(NSString*)elementId andStyle:(NSString*)styleClass andSubViews:(SubViewBlock)subViewBlock;


/**
 * Builds a `UIScrollView` with the specified style class.
 */
+ (UIScrollView*) scrollViewWithStyle:(NSString*)styleClass;
+ (UIScrollView*) scrollViewWithId:(NSString*)elementId;

/**
 * Builds a `UIScrollView` with the specified style class and adds the subviews from the specified `SubViewBlock`.
 */
+ (UIScrollView*) scrollViewWithStyle:(NSString*)styleClass andSubViews:(SubViewBlock)subViewBlock;
+ (UIScrollView*) scrollViewWithId:(NSString*)elementId andStyle:(NSString*)styleClass andSubViews:(SubViewBlock)subViewBlock;


/**
 * Builds a `UITableView` with the specified style class.
 */
+ (UITableView*) tableViewWithStyle:(NSString*)styleClass andTableViewStyle:(UITableViewStyle)tableViewStyle;
+ (UITableView*) tableViewWithId:(NSString*)elementId andTableViewStyle:(UITableViewStyle)tableViewStyle;

/**
 * Builds a `UITableView` with the specified style class and adds the subviews from the specified `SubViewBlock`.
 */
+ (UITableView*) tableViewWithStyle:(NSString*)styleClass andTableViewStyle:(UITableViewStyle)tableViewStyle andSubViews:(SubViewBlock)subViewBlock;

/**
 * Builds a `UITableView` with the specified implementation class and style class, and adds the subviews from the specified `SubViewBlock`.
 */
+ (UITableView*) tableViewOfClass:(Class)clazz withStyle:(NSString*)styleClass andTableViewStyle:(UITableViewStyle)tableViewStyle andSubViews:(SubViewBlock)subViewBlock;
+ (UITableView*) tableViewOfClass:(Class)clazz withId:(NSString*)elementId andStyle:(NSString*)styleClass andTableViewStyle:(UITableViewStyle)tableViewStyle andSubViews:(SubViewBlock)subViewBlock;


/**
 * Builds a `UIWebView` with the specified style class.
 */
+ (UIWebView*) webViewWithStyle:(NSString*)styleClass;
+ (UIWebView*) webViewWithId:(NSString*)elementId;

/**
 * Builds a `UIWebView` with the specified style class and adds the subviews from the specified `SubViewBlock`.
 */
+ (UIWebView*) webViewWithStyle:(NSString*)styleClass andSubViews:(SubViewBlock)subViewBlock;
+ (UIWebView*) webViewWithId:(NSString*)elementId andStyle:(NSString*)styleClass andSubViews:(SubViewBlock)subViewBlock;


/**
 * Builds a `UIActivityIndicatorView` with the specified style class.
 */
+ (UIActivityIndicatorView*) activityIndicatorViewWithStyle:(NSString*)styleClass;
+ (UIActivityIndicatorView*) activityIndicatorViewWithId:(NSString*)elementId;

/**
 * Builds a `UIButton` with the specified style class.
 */
+ (UIButton*) buttonWithStyle:(NSString*)styleClass;
+ (UIButton*) buttonWithId:(NSString*)elementId;

/**
 * Builds a `UIButton` with the specified style class.
 */
+ (UIButton*) buttonWithStyle:(NSString*)styleClass andButtonType:(UIButtonType)buttonType;

/**
 * Builds a `UILabel` with the specified style class.
 */
+ (UILabel*) labelWithStyle:(NSString*)styleClass;
+ (UILabel*) labelWithId:(NSString*)elementId;

/**
 * Builds a `UIProgressView` with the specified style class.
 */
+ (UIProgressView*) progressViewWithStyle:(NSString*)styleClass;
+ (UIProgressView*) progressViewWithId:(NSString*)elementId;

/**
 * Builds a `UISlider` with the specified style class.
 */
+ (UISlider*) sliderWithStyle:(NSString*)styleClass;
+ (UISlider*) sliderWithId:(NSString*)elementId;

/**
 * Builds a `UIStepper` with the specified style class.
 */
+ (UIStepper*) stepperWithStyle:(NSString*)styleClass;
+ (UIStepper*) stepperWithId:(NSString*)elementId;

/**
 * Builds a `UISwitch` with the specified style class.
 */
+ (UISwitch*) switchWithStyle:(NSString*)styleClass;
+ (UISwitch*) switchWithId:(NSString*)elementId;

/**
 * Builds a `UITextField` with the specified style class.
 */
+ (UITextField*) textFieldWithStyle:(NSString*)styleClass;
+ (UITextField*) textFieldWithId:(NSString*)elementId;

/**
 * Builds a `UITextView` with the specified style class.
 */
+ (UITextView*) textViewWithStyle:(NSString*)styleClass;
+ (UITextView*) textViewWithId:(NSString*)elementId;

/**
 * Builds a `UITableViewCell` with the specified style class.
 */
+ (UITableViewCell*) tableViewCellWithStyle:(NSString*)styleClass andReuseIdentifier:(NSString*)reuseIdentifier;

/**
 * Builds a `UITableViewCell` with the specified style class.
 */
+ (UITableViewCell*) tableViewCellWithStyle:(NSString*)styleClass andCellStyle:(UITableViewCellStyle)cellStyle andReuseIdentifier:(NSString*)reuseIdentifier;

@end
