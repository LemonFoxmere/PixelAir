#import <Cocoa/Cocoa.h>
#import <QtGui/qwindowdefs.h>

void customizeMacOSWindow(WId nativeWinId) {
  // WId -> NSView
  NSView *nativeView = (__bridge NSView *)(reinterpret_cast<void *> (nativeWinId));
  if(!nativeView) return;

  NSWindow *nsw = [nativeView window];
  if (!nsw) {
      return; // fail if the window is invalid
  }

  NSUInteger styleMask = [nsw styleMask];
  styleMask |= NSWindowStyleMaskFullSizeContentView;
  [nsw setStyleMask:styleMask];

  NSToolbar *toolbar = [[NSToolbar alloc] initWithIdentifier:@"main"];
  toolbar.allowsUserCustomization = NO;
  toolbar.allowsExtensionItems = NO;
  toolbar.allowsDisplayModeCustomization = NO;

  nsw.toolbar = toolbar;

  nsw.movableByWindowBackground = YES;
  nsw.titlebarAppearsTransparent = YES;
}
