#ifndef ___ISPY_DEFINED___
#import "iSpyServer/iSpyHTTPServer.h"
#import "iSpyServer/shellWebsocket.h"
#import "iSpyServer/iSpyWebsocket.h"
#import "iSpy.rpc.h"
#include "iSpy.msgSend.whitelist.h"
#include "iSpy.instance.h"

/*
    Adds a nice "containsString" method to NSString
*/
@interface NSString (iSpy)
{

}

-(BOOL) containsString:(NSString*)substring;

@end



/*
	Parent server that controls the HTTP server and RPC server
    and makes them talk to each other all nice like
*/
@interface iSpyServer : NSObject {

}

@property (assign) iSpyHTTPServer *httpServer;
@property (assign) iSpyWebSocket *iSpyWebSocket;
@property (assign) NSMutableDictionary *plist;
@property (assign) RPCHandler *rpcHandler;
-(void) configureWebServer;
-(int) getListenPortFor:(NSString *) key fallbackTo: (int) fallback;
-(NSDictionary *)dispatchRPCRequest:(NSString *) JSONString;

@end


/*
	Functionality that's exposed to Cycript.
*/
@interface iSpy : NSObject {
//	Class *classList;
}
@property (assign) iSpyServer *webServer;
@property (assign) NSString *globalStatusStr;
@property (assign) char *bundle;
@property (assign) NSString *bundleId;
@property (assign) BOOL isInstanceTrackingEnabled;
@property (assign) NSMutableDictionary *trackedInstances;
@property (assign) NSMutableDictionary *msgSendWhitelist;
@property (assign) ClassMap_t *classWhitelist;
@property (assign) InstanceTracker *instanceTracker;

+(iSpy *)sharedInstance;
-(void)initializeAllTheThings;
-(NSDictionary *) getNetworkInfo;
/*
-(NSString *) instance_dumpAllInstancesWithPointers;
-(NSString *) instance_dumpAppInstancesWithPointers;
-(NSArray *) instance_dumpAppInstancesWithPointersArray;
-(NSDictionary *) instance_dumpAppInstancesWithPointersDict;
-(int) instance_numberOfTrackedInstances;
-(void) instance_searchInstances:(NSString *)forName;
*/
-(BOOL) instance_getTrackingState;
-(void) instance_enableTracking;
-(void) instance_disableTracking;
-(NSDictionary *)keyChainItems;
-(unsigned int)ASLR;
-(NSDictionary *)infoForMethod:(SEL)selector inClass:(Class)cls;
-(NSDictionary *)infoForMethod:(SEL)selector inClass:(Class)cls isInstanceMethod:(BOOL)isInstance;
-(id)iVarsForClass:(NSString *)className;
-(id)propertiesForClass:(NSString *)className;
-(id)methodsForClass:(NSString *)className;
-(NSArray *)methodListForClass:(NSString *)className;
-(id)classes;
-(id)classesWithSuperClassAndProtocolInfo;
-(id)protocolsForClass:(NSString *)className;
-(id)propertiesForProtocol:(Protocol *)protocol;
-(id)methodsForProtocol:(Protocol *)protocol;
-(NSDictionary *)protocolDump;
-(NSDictionary *)classDump;
-(NSDictionary *)classDumpClass:(NSString *)className;
-(void) msgSend_enableLogging;
-(void) msgSend_disableLogging;
+(BOOL)isClassFromApp:(NSString *)className;
@end


/*
	Helper functions.
*/

char *bf_get_type_from_signature(char *typeStr);
#else
#define ___ISPY_DEFINED___
#endif
