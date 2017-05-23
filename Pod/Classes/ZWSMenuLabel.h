//
//  ZWSMenuLabel.h
//

#import <Foundation/Foundation.h>
#import "ZWSFlowMenu.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZWSMenuLabel : UILabel <ZWSMenuAppearance>

@property (nonatomic, strong, nullable) UIFont *highlightedFont;

- (void)transformColor:(float)progress;

- (void)transformFont:(float)progress;

@end

NS_ASSUME_NONNULL_END
