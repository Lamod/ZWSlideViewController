//
//  JHSBrandSectionBar.h
//

#import <UIKit/UIKit.h>
#import "ZWSFlowMenu.h"
#import "ZWSMenuLabel.h"

NS_ASSUME_NONNULL_BEGIN

@protocol ZWSSectionBarDelegate;

@interface ZWSSectionBar : ZWSFlowMenu {
    UITapGestureRecognizer *_tapGestureRecognizer;
    NSArray *_titles;
}

@property (nonatomic, strong, nullable) UIColor *textColor; // Default: grayColor
@property (nonatomic, strong, nullable) UIColor *highlightedTextColor; // Default: redColor
@property (nonatomic, assign) CGFloat indicatorHeight; // Default: 2px
/**
 @return `highlightedTextColor` if the value is nil
 */
@property (nonatomic, strong, nullable) UIColor *indicatorColor;

@property (nonatomic, strong, nullable) UIFont *nomarlTextFont; // Default: 14.0f
@property (nonatomic, strong, nullable) UIFont *selectedTextFont; // Default: 15.0f

@property(nonatomic, strong, nullable) NSArray<NSString *> *titles;
@property(nonatomic, assign) CGSize itemSize;

@property(nonatomic, weak, nullable) id<ZWSSectionBarDelegate> barDelegate;

- (nullable UIView *)itemForTitle:(NSString *)title;

@end

@protocol ZWSSectionBarDelegate<NSObject>

@optional

- (void)sectionBar:(ZWSSectionBar *)sectionBar didSelectAtInedx:(NSInteger)index;

- (void)didCreateItemView:(UIView *)itemView;

- (UIView *)menuItemWithTitle:(NSString *)title;

@end

NS_ASSUME_NONNULL_END
