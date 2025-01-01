#import <Cocoa/Cocoa.h>
#import <QtGui/qwindowdefs.h>

// Toolbar delegate to hide the toolbar in fullscreen
@interface WindowDelegate : NSObject <NSWindowDelegate>
@end

@implementation WindowDelegate
- (NSApplicationPresentationOptions)window:(NSWindow *)window willUseFullScreenPresentationOptions:(NSApplicationPresentationOptions)proposedOptions {
    return NSApplicationPresentationAutoHideToolbar | NSApplicationPresentationAutoHideMenuBar | NSApplicationPresentationFullScreen;
}
- (void)windowWillClose:(NSNotification *)notification {
    [NSApp terminate:nil];
}
@end

void customizeMacOSWindow(WId nativeWinId) {
  // WId -> NSView
  NSView *nativeView = (__bridge NSView *)(reinterpret_cast<void *> (nativeWinId));
  if(!nativeView) return;

  NSWindow *nsw = (NSWindow *)[nativeView window];
  if (!nsw) {
      return; // Fail if the window is invalid
  }

  NSUInteger styleMask = [nsw styleMask];
  styleMask |= NSWindowStyleMaskTitled;
  styleMask |= NSWindowStyleMaskClosable;
  styleMask |= NSWindowStyleMaskResizable;
  styleMask |= NSWindowStyleMaskFullSizeContentView;
  [nsw setStyleMask:styleMask];

  NSToolbar *toolbar = [[NSToolbar alloc] initWithIdentifier:@"main"];
  toolbar.allowsUserCustomization = NO;
  toolbar.allowsExtensionItems = NO;
  toolbar.allowsDisplayModeCustomization = NO;

  nsw.toolbar = toolbar;
  nsw.toolbarStyle = NSWindowToolbarStyleUnified;
  nsw.titleVisibility = NSWindowTitleHidden;

  nsw.titlebarAppearsTransparent = YES;

  WindowDelegate  *windowDelegate = [[WindowDelegate  alloc] init];
  nsw.delegate = windowDelegate;
}
