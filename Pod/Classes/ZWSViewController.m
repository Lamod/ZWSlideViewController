//
//  ZWSViewController.m
//  ZWSlideViewController
//

#import "ZWSViewController.h"

@interface ZWSViewController ()

@end

@implementation ZWSViewController

@dynamic menuTitles;

- (instancetype)initWithCoder:(NSCoder *)coder
{
    self = [super initWithCoder:coder];
    if (self) {
        [self initSelf];
    }
    return self;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        [self initSelf];
    }
    return self;
}

- (void)initSelf
{
    self.useTransform3DEffects = NO;
    
    if (!_sectionBar) {
        _sectionBar = [[ZWSSectionBar alloc] init];
        _sectionBar.barDelegate = self;
        _sectionBar.menuInsets   = UIEdgeInsetsMake(0, 10, 0, 10);
        _sectionBar.backgroundColor = [UIColor whiteColor];
    }
    
    if (!_pagingView) {
        _pagingView = [[ZWSPagingView alloc] init];
        _pagingView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;
        _pagingView.pagingDataSource = self;
        _pagingView.pagingDelegate = self;
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.edgesForExtendedLayout = UIRectEdgeNone;
    
    [self loadData];
    
    [self refreshViews];
}

- (CGFloat)menuHeight
{
    if (!_menuHeight) {
        return 44.0f;
    }
    return _menuHeight;
}

- (NSArray<NSString *> *)menuTitles {
    return _sectionBar.titles;
}

- (void)setMenuTitles:(NSArray<NSString *> *)menuTitles {
    _sectionBar.titles = menuTitles;
    [_pagingView reloadPages];
}

#pragma mark - Public methods

- (void)loadData
{
    // do nothing
}

- (void)refreshViews
{
    _sectionBar.frame = CGRectMake(self.view.bounds.origin.x, self.view.bounds.origin.y, self.view.bounds.size.width, self.menuHeight);
    [self.view addSubview:_sectionBar];
    
    _pagingView.frame = CGRectMake(self.view.bounds.origin.x, self.sectionBar.frame.size.height, self.view.bounds.size.width, self.view.bounds.size.height - self.sectionBar.frame.size.height);
    [self.view insertSubview:_pagingView belowSubview:_sectionBar];
    
    [_sectionBar reloadItems];
    [_pagingView reloadPages];
}

#pragma mark - Override Methods

- (UIView *)contentViewForPage:(ZWSPage *)page atIndex:(NSInteger)index
{
    // subclass could override
    return nil;
}

#pragma mark - ZWSPagingViewDataSource

- (NSInteger)numberOfPagesInPagingView:(ZWSPagingView *)pagingView {
    return [[self menuTitles] count];
}

- (ZWSPage *)pagingView:(ZWSPagingView *)pagingView pageForIndex:(NSInteger)index {
    ZWSPage *page = [pagingView dequeueReusablePage];
    if (!page) {
        page = [ZWSPage new];
    }
    
    return page;
}

#pragma mark - ZWSPagingViewDelegate

- (void)pagingView:(ZWSPagingView *)pagingView didRemovePage:(ZWSPage *)page {
    if (pagingView.centerPage != page) {
        return;
    }
}

- (void)pagingView:(ZWSPagingView *)pagingView willMoveToPage:(ZWSPage *)page {
    page.contentView = [self contentViewForPage:(ZWSPage *)page atIndex:[pagingView indexOfPage:page]];
}

- (void)pagingView:(ZWSPagingView *)pagingView didMoveToPage:(ZWSPage *)page {
}

- (void)pagingViewLayoutChanged:(ZWSPagingView *)pagingView {
    if (self.useTransform3DEffects) {
        [self transform3DEffects:pagingView];
    }
    
    [_sectionBar moveToMenuAtFloatIndex:pagingView.floatIndex animated:YES];
}

#pragma mark - ZWSSectionBarDelegate

- (void)sectionBar:(ZWSSectionBar *)sectionBar didSelectAtInedx:(NSInteger)index
{
    [_pagingView moveToPageAtFloatIndex:index animated:YES];
}

- (void)didCreateItemView:(UIView *)itemView
{
    
}

#pragma mark - Private Methods

- (void)transform3DEffects:(ZWSPagingView *)pagingView
{
    CGFloat ratio = .0, scale;
    for (ZWSPage *page in pagingView.visiblePages) {
        ratio = [pagingView widthInSight:page] / CGRectGetWidth(page.frame);
        scale = .9 + ratio * .1;
        
        CATransform3D t = CATransform3DMakeScale(scale, scale, scale);
        
        page.layer.transform = t;
    }
}


@end
