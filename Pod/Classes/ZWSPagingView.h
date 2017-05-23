//
//  ZWSPagingView.h
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ZWSPage : UIView {
    NSInteger _index;
}

@property(nonatomic, strong, nullable) UIView *contentView;

@end

@protocol ZWSPagingViewDelegate;
@protocol ZWSPagingViewDataSource;

@interface ZWSPagingView : UIScrollView<UIScrollViewDelegate> {
    BOOL _scrollInfinitelyEnabled;

    NSInteger _numberOfPages;

    NSMutableSet<ZWSPage *> *_visiblePages;
    NSMutableSet<ZWSPage *> *_recycledPages;

    ZWSPage * _Nullable _centerPage;

    __weak id<ZWSPagingViewDelegate> _Nullable _pagingDelegate;
    __weak id<ZWSPagingViewDataSource> _Nullable _pagingDataSource;

    __weak id _Nullable _actualDelegate;
}

@property(nonatomic, assign) BOOL scrollInfinitelyEnabled;

@property(nonatomic, weak, nullable) id<ZWSPagingViewDelegate> pagingDelegate;
@property(nonatomic, weak, nullable) id<ZWSPagingViewDataSource> pagingDataSource;

@property(nonatomic, readonly, nullable) ZWSPage *centerPage;
@property(nonatomic, readonly) NSSet<ZWSPage *> *visiblePages;

// it will be pre-fetched content and cached for next page
@property(nonatomic, getter=isPreload) BOOL preload;

- (NSInteger)indexOfPage:(ZWSPage *)page;
- (NSInteger)indexOfCenterPage;

- (ZWSPage * _Nullable)pageAtLocation:(CGPoint)location;

- (CGFloat)widthInSight:(ZWSPage *)page;

- (float)floatIndex;
- (void)moveToPageAtFloatIndex:(float)index animated:(BOOL)animated;

- (ZWSPage * _Nullable)dequeueReusablePage;
- (void)reloadPages;

@end

@protocol ZWSPagingViewDataSource

@required
- (NSInteger)numberOfPagesInPagingView:(ZWSPagingView *)pagingView;
- (ZWSPage *)pagingView:(ZWSPagingView *)pagingView pageForIndex:(NSInteger)index;

@end

@protocol ZWSPagingViewDelegate

- (void)pagingView:(ZWSPagingView *)pagingView didRemovePage:(ZWSPage *)page;
- (void)pagingView:(ZWSPagingView *)pagingView willMoveToPage:(ZWSPage *)page;
- (void)pagingView:(ZWSPagingView *)pagingView didMoveToPage:(ZWSPage *)page;
- (void)pagingViewLayoutChanged:(ZWSPagingView *)pagingView;

@end

NS_ASSUME_NONNULL_END
