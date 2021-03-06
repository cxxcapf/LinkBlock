//
//  NSObject+LinkBlock.h

//
//  Created by NOVO on 15/8/12.
//  Copyright (c) 2015年 NOVO. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface NSObject(LinkBlock)
#pragma mark - 方式
/** 
 <- linkEnd>获取链条返回值，并将错误转nil，NSNull也以nil返回
 ... = linkObj(..)...linkEnd;
 ... = linkObj(..)...linkIf(...)...linkEnd;
 */
@property (nonatomic,copy,readonly) id           linkEnd;
/**
 <- ends>多对象链式编程获取多个链条返回值，并将错误转nil，NSNull也以nil返回
 ... = linkObj(...)...linkLoop(...)...linkEnds;
 */
@property (nonatomic,copy,readonly) NSArray*     linkEnds;
/** 
 <^(NSUInteger idx)>多对象链式编程获取某一链条返回值，并将错误转nil，NSNull也以nil返回
 ... = linkObj(...)...linkLoop(...)...linkEndsAt(index);
 */
@property (nonatomic,copy,readonly) id           (^linkEndsAt)(NSUInteger idx);
/** 
 <^(id* toObject)>将当前对象赋值到变量
 ...setTo(&...);
 */
@property (nonatomic,copy,readonly) NSObject*    (^setTo)(id* toObject);
/** 
 <^(id obj)>使新对象加入链条
 ...linkAnd(obj1)...linkAnd(obj2)...
 ... = ...linkAnd(obj1)...linkAnd(obj2)...linkEnds;
 */
@property (nonatomic,copy,readonly) NSObject*    (^linkAnd)(id obj);
/**
 <^(id obj)>以新对象执行其后链条，可以与linkIf，linkElse配合
 linkObjs(,,,)...linkTo(aNewObj)...
 ...linkIf(...)...linkTo(aNewObj)...linkElse...
 */
@property (nonatomic,copy,readonly) NSObject*    (^linkTo)(id obj);
/** 
 <^(NSUInteger idx)>使多链条中移除一个
 linkObjs(,,,)...linkOut(index)...
 */
@property (nonatomic,copy,readonly) NSObject*    (^linkOut)(NSUInteger idx);
/** 
 <^(NSUInteger idx)>取出多链条中一个
 linkObjs(,,,)...linkAt(index)...
 */
@property (nonatomic,copy,readonly) NSObject*    (^linkAt)(NSUInteger idx);
/**
 <^()>取出多链条中第一个
 linkObjs(,,,)...linkFirstObj...
 */
@property (nonatomic,copy,readonly) NSObject*    linkFirstObj;
/**
 <^()>取出多链条中最后一个
 linkObjs(,,,)...linkLastObj...
 */
@property (nonatomic,copy,readonly) NSObject*    linkLastObj;
/** 
 <^(NSUInteger count)>使其后的链条复制指定次数的重复执行效果。所以...linkLoop(...)...m_arrAddObj([NSObject new])...添加的是同一个对象。这里添加不同对象应使用方法linkLoopIn:block:。
 ...linkLoop(count)...
 */
@property (nonatomic,copy,readonly) NSObject*    (^linkLoop)(NSUInteger count);
/** 
 <^()>根据条件是否中断其后语句，如果当前语句已中断则由当前条件决定其后是否执行；取值需使用end
 ...linkIf(...)...linkIf(...)...linkElse...
 ... = ...linkLoop(...)...linkIf(...)...linkEnds();
 */
@property (nonatomic,copy,readonly) NSObject*    (^linkIf)(BOOL condition);
/** 
 <^()>从中断语句中恢复执行其后语句，与前一个linkIf配合使用；取值需使用end
 ...linkIf(...)...linkIf(...)...linkElse...
 */
@property (nonatomic,copy,readonly) NSObject*    linkElse;
/**
 <^()>使其后语句跳空至末尾（优先级高于其他条件）；可与分支配合；取值需使用end
 ...[linkInBlock:^(NSObject* fromObj){
    if(...){
        ...linkReturn;
    }
 }]...linkEnd;
 */
@property (nonatomic,copy,readonly) NSObject*    linkReturn;
/** 
 链条分支，返回源对象，在链条内处理新分支
 ...[linkInBlock:^(NSObject* link){
    link...
 }]...
 */
- (NSObject*)linkInBlock:(void(^)(NSObject* link))block;

/**
 异步在主队列中执行block
 */
- (NSObject*)linkAsy_main_queue:(void(^)(NSObject* link))block;

/**
 异步在全局队列中执行block
 */
- (NSObject*)linkAsy_global_queue:(void(^)(NSObject* link))block;

/**
 执行指定次数block
 */
- (NSObject*)linkLoopIn:(NSUInteger)count block:(void(^)(NSObject* link, NSUInteger index))block;

/**
 在主队列中延迟执行block
 */
- (NSObject*)linkAfterIn:(double)time block:(void(^)(NSObject* link))block;

#pragma mark - 功能
/** <^()>NSLog() */
@property (nonatomic,copy,readonly) NSObject*    (^nslog)();
/** <^(NSString* title)>输出对象前增加标识语 */
@property (nonatomic,copy,readonly) NSObject*    (^nslogTitle)(NSString* title);
/** <^(NSString* title)>独立在语句中输出信息，并不打印对象 */
@property (nonatomic,copy,readonly) NSObject*    (^logInfo)(NSString* info);
/** <^()>将对象以字典的形式进行打印，其中对所有容器类型进行遍历转换 */
@property (nonatomic,copy,readonly) NSObject*    (^po)();
/** <^()>将对象以字典的形式进行打印 */
@property (nonatomic,copy,readonly) NSObject*    (^poNoDeep)();
/** <^(NSString* key)>输出对象Key对应的值 */
@property (nonatomic,copy,readonly) NSObject*    (^nslogValueForKey)(NSString* key);
/** <^(NSString* key)> */
@property (nonatomic,copy,readonly) NSObject*    (^nslogValueForKeyPath)(NSString* key);

#pragma mark - Runtime
/** <^(NSString* key)> */
@property (nonatomic,copy,readonly) id           (^valueForKey)(NSString* key);
/** <^(id value,NSString* key)> */
@property (nonatomic,copy,readonly) NSObject*    (^setValueForKey)(id value,NSString* key);
/** <^(NSString* key)> */
@property (nonatomic,copy,readonly) id           (^valueForKeyPath)(NSString* key);
/** <^(id value,NSString* key)> */
@property (nonatomic,copy,readonly) NSObject*    (^setValueForKeyPath)(id value,NSString* key);
/** <^(NSString* key)> */
@property (nonatomic,copy,readonly) id           (^valueForKeySafe)(NSString* key);
/** <^(id value,NSString* key)> */
@property (nonatomic,copy,readonly) NSObject*    (^setValueForKeySafe)(id value,NSString* key);
/** <^(NSString* key)> */
@property (nonatomic,copy,readonly) id           (^valueForKeyPathSafe)(NSString* key);
/** <^(id value,NSString* key)> */
@property (nonatomic,copy,readonly) NSObject*    (^setValueForKeyPathSafe)(id value,NSString* key);
/** <^(Class classKind)> */
@property (nonatomic,copy,readonly) BOOL         (^isKindOf)( __unsafe_unretained Class classKind);
@property (nonatomic,copy,readonly) NSNumber*    (^isKindOf_n)( __unsafe_unretained Class classKind);
/** <^(Class classKind)> */
@property (nonatomic,copy,readonly) BOOL         (^isSubClassOf)( __unsafe_unretained Class classKind);
@property (nonatomic,copy,readonly) NSNumber*    (^isSubClassOf_n)( __unsafe_unretained Class classKind);
/** <^(SEL theSEL)> */
@property (nonatomic,copy,readonly) BOOL         (^isRespondsSEL)(SEL theSEL);
@property (nonatomic,copy,readonly) NSNumber*    (^isRespondsSEL_n)(SEL theSEL);
/** <^()> */
@property (nonatomic,copy,readonly) NSString*    (^className)();
/** <^()> */
@property (nonatomic,copy,readonly) NSString*    (^superclassName)();

/** 是否是常见基础类型 */
+ (BOOL)classIsFoundation;
/** 当前类型是否包含属性（@property value），不包括父类 */
+ (BOOL)classContainProperty:(NSString*)property;
/** 当前类型是否包含成员变量（_value）不包括父类 */
+ (BOOL)classContainIvar:(NSString*)ivarName;
/** 获取当前类型的成员变量名列表 */
+ (NSArray<NSString*>*)classGetIvarList;
/** 获取当前类型的属性名列表（@property value） */
+ (NSArray<NSString*>*)classGetPropertyList;
/**
 获取当前类型属性的类型字符串

 @param key 属性名

 @return 属性类型的字符串；基本类型数据返回形如：i,q,l...(参考：property type encodings)
 */
+ (NSString*)classGetPropertyType:(NSString*)key;
/**
 *  获取当前类型及父类的属性名列表（不包含NSObject以及NSObject扩展属性）
 *
 *  @param includeFoundation 是否包含基础类型
 */
+ (NSArray<NSString*>*)classGetAllPropertyList:(BOOL)includeFoundation;
/** 获取实例方法名列表 */
- (NSArray<NSString*>*)objGetInstanceMethodList;
/** 获取类方法名列表 */
+ (NSArray<NSString*>*)classGetClassMethodList;
/** 获取协议名列表 */
+ (NSArray<NSString*>*)classGetProtocolList;
/**
 *  遍历所有类
 *
 *  @param includeFoundation 遍历时是否包含基础类型
 */
+ (void)classEnumerateUsingBlock:(void(^)(Class clazz , BOOL* stop))block
               includeFoundation:(BOOL)includeFoundation;

/**
 *  遍历所有属性（propertyType：属性类型的字符串；基本类型数据形如：i,q,l...(参考：property type encodings或objValueRandom内部实现)
 *
 *  @param includeFoundation 遍历时是否包含基础类型
 */
+ (void)classPropertysEnumerateUsingBlock:(void(^)(Class clazz,NSString* propertyName,NSString* propertyType,BOOL* stop))block
               includeFoundation:(BOOL)includeFoundation;

#pragma mark - NSObject
/** <^(id obj)>UIView时为添加子视图,String时为拼接字符串,Array等集合类型为添加子项 */
@property (nonatomic,copy,readonly) NSObject*    (^objAdd)(id obj);
/** <^(id obj)>UIView时为添加子视图,String时为拼接字符串,Array等集合类型为添加子项 */
@property (nonatomic,copy,readonly) NSObject*    (^objAddTo)(id obj);
/** <^(id obj)>UIView时为添加子视图,String时为拼接字符串,Array等集合类型为添加子项，返回为入参对象 */
@property (nonatomic,copy,readonly) NSObject*    (^objAddTo_linkTo)(id obj);
/** <^(id obj , NSUInteger idx)>UIView时为添加子视图,String时为拼接字符串,Array等集合类型为添加子项 */
@property (nonatomic,copy,readonly) NSObject*    (^objInsert)(id obj , NSUInteger idx);
/** <^(id obj , NSUInteger idx)>UIView时为添加子视图,String时为拼接字符串,Array等集合类型为添加子项 */
@property (nonatomic,copy,readonly) NSObject*    (^objInsertTo)(id obj , NSUInteger idx);
/** <^(id obj , NSUInteger idx)>UIView时为添加子视图,String时为拼接字符串,Array等集合类型为添加子项，返回为入参对象 */
@property (nonatomic,copy,readonly) NSObject*    (^objInsertTo_linkTo)(id obj , NSUInteger idx);
/** <^(id obj)>UIView时为移除子视图,String时为移除字符串,Array等集合类型为移除子项,Dictionary时为移除键相关的项 */
@property (nonatomic,copy,readonly) NSObject*    (^objRemove)(id obj);
/** <^(id obj)>UIView时为移除子视图,String时为移除字符串,Array等集合类型为移除子项,Dictionary时为移除键相关的项 */
@property (nonatomic,copy,readonly) NSObject*    (^objRemoveFrom)(id obj);
/** <^(id obj)>UIView时为移除子视图,String时为移除字符串,Array等集合类型为移除子项,Dictionary时为移除键相关的项，返回为入参对象 */
@property (nonatomic,copy,readonly) NSObject*    (^objRemoveFrom_linkTo)(id obj);
/** <^()> */
@property (nonatomic,copy,readonly) NSObject*    (^objCopy)();
/** <^()> */
@property (nonatomic,copy,readonly) NSObject*    (^objMutableCopy)();
/** <^()> 通过序列化的方式复制一份完全独立的对象 */
@property (nonatomic,copy,readonly) NSObject*    (^objCopyByArchive)();
/**
 *  <^()>
 *  对象及可能包含的子对象全部转为json相关的可变类型
 * （NSMutableArray,NSMutableDictionary,NSMutableString）
 */
@property (nonatomic,copy,readonly) NSObject*    (^objMutableCopyDeep)();
/** <^()> */
@property (nonatomic,copy,readonly) BOOL         (^objIsNSNull)();
@property (nonatomic,copy,readonly) NSNumber*    (^objIsNSNull_n)();
/** <^(id obj)> */
@property (nonatomic,copy,readonly) BOOL         (^objIsEqual)(id obj);
@property (nonatomic,copy,readonly) NSNumber*    (^objIsEqual_n)(id obj);
/** <^(id obj,...)> */
@property (nonatomic,copy,readonly) BOOL         (^objIsEqualToEach)(id obj,...);
@property (nonatomic,copy,readonly) NSNumber*    (^objIsEqualToEach_n)(id obj,...);
/** <^(NSArray* arr)> */
@property (nonatomic,copy,readonly) BOOL         (^objIsEqualToEachInArray)(NSArray* arr);
@property (nonatomic,copy,readonly) NSNumber*    (^objIsEqualToEachInArray_n)(NSArray* arr);
/** <^(id obj,...)> */
@property (nonatomic,copy,readonly) BOOL         (^objIsEqualToSomeone)(id obj,...);
@property (nonatomic,copy,readonly) NSNumber*    (^objIsEqualToSomeone_n)(id obj,...);
/** <^(NSArray* arr)> */
@property (nonatomic,copy,readonly) BOOL         (^objIsEqualToSomeoneInArray)(NSArray* arr);
@property (nonatomic,copy,readonly) NSNumber*    (^objIsEqualToSomeoneInArray_n)(NSArray* arr);
/** <^(Class theCalss)>必须获取该类型的对象，若类型不符则返回该类型的初始化对象 */
@property (nonatomic,copy,readonly) NSObject*    (^objMustType)(Class theCalss);
/** <^(NSString* key)>将BOOL或NSNumber(BOOL)属性字段值反转 */
@property (nonatomic,copy,readonly) NSObject*    (^objBoolReverseForKey)(NSString* key);
/** <^(id delegate)>设置字段delegate的值 */
@property (nonatomic,copy,readonly) NSObject*    (^objSetDelegate)(id delegate);
/** <^(NSArray* withoutKeys)>将自定义对象随机赋值，只包含字符串类型和数字类型 */
@property (nonatomic,copy,readonly) NSObject*    (^objValueRandom)();
#pragma mark - About NSString
/** <^()>NSDate,NSString,NSArray,NSDictionary等对象转成json的字符串 */
@property (nonatomic,copy,readonly) NSString*    (^objToJsonString)();

#pragma mark - About NSMutableArray
/** <^(NSMutableArray* arr)>将对象添加到 */
@property (nonatomic,copy,readonly) NSObject*    (^objAddToArr)(NSMutableArray* arr);
/** <^(NSMutableArray* arr)> */
@property (nonatomic,copy,readonly) NSObject*    (^objRemoveFromArr)(NSMutableArray* arr);
/** <^(NSArray* inArr)>在数组中的前一个元素，无返回nil */
@property (nonatomic,copy,readonly) NSObject*    (^objBeforeInArr)(NSArray* inArr);
/** <^(NSArray* inArr)>在数组中的后一个元素无返回nil */
@property (nonatomic,copy,readonly) NSObject*    (^objNextInArr)(NSArray* inArr);
/** <^(NSArray* inArr)>对象是否在数组中 */
@property (nonatomic,copy,readonly) BOOL         (^objIsInArr)(NSArray* inArr);
@property (nonatomic,copy,readonly) NSNumber*    (^objIsInArr_n)(NSArray* inArr);
#pragma mark - About NSMutableDictionary
/** <^(NSMutableDictionary* dict, id<NSCopying> key)>将对象设置到字典 */
@property (nonatomic,copy,readonly) NSObject*    (^objSetToDict)(NSMutableDictionary* dict, id<NSCopying> key);
/** <^(NSMutableDictionary* dict)>对象是否在字典值的集合中 */
@property (nonatomic,copy,readonly) BOOL         (^objIsInDictValues)(NSMutableDictionary* dict);
@property (nonatomic,copy,readonly) NSNumber*    (^objIsInDictValues_n)(NSMutableDictionary* dict);
/** <^(NSMutableDictionary* dict)>对象是否在字典键的集合中 */
@property (nonatomic,copy,readonly) BOOL         (^objIsInDictKeys)(NSMutableDictionary* dict);
@property (nonatomic,copy,readonly) NSNumber*    (^objIsInDictKeys_n)(NSMutableDictionary* dict);
/**
 *  <^(BOOL includeFoundation)>
 *  将当前对象转字典（如果对象为容器类型则对值进行一次转换）
 *  includeFoundationProperty：是否包含基础类型的属性
 */
@property (nonatomic,copy,readonly) NSDictionary*(^objToNSDictionaryNoDeep)(BOOL includeFoundation);
/**
 *  <^(BOOL includeFoundation)>
 *  对象转字典（对所有属性进行层次遍历，对容器对象的值也是）
 *  includeFoundationProperty：是否包含基础类型的属性
 */
@property (nonatomic,copy,readonly) NSDictionary*(^objToNSDictionary)(BOOL includeFoundation);




//MARK: 明确对象类型
-                  (NSString*)                  ofNSString;
-                  (NSMutableString*)           ofNSMutableString;
-                  (NSArray*)                   ofNSArray;
-                  (NSMutableArray*)            ofNSMutableArray;
-                  (NSDictionary*)              ofNSDictionary;
-                  (NSMutableDictionary*)       ofNSMutableDictionary;
-                  (NSAttributedString*)        ofNSAttributedString;
-                  (NSMutableAttributedString*) ofNSMutableAttributedString;
-                  (NSURL*)                     ofNSURL;
-                  (NSUserDefaults*)            ofNSUserDefaults;
-                  (NSNumber*)                  ofNSNumber;
-                  (NSValue*)                   ofNSValue;
-                  (UIImage*)                   ofUIImage;
-                  (NSDate*)                    ofNSDate;
-                  (NSData*)                    ofNSData;
-                  (UIView*)                    ofUIView;
-                  (UILabel*)                   ofUILabel;
-                  (UIControl*)                 ofUIControl;
-                  (UIButton*)                  ofUIButton;
-                  (UIScrollView*)              ofUIScrollView;
-                  (UIImageView*)               ofUIImageView;
-                  (UITableView*)               ofUITableView;
-                  (UIColor*)                   ofUIColor;
-                  (UIViewController*)          ofUIViewController;
-                  (UITextField*)               ofUITextField;
-                  (UITextView*)                ofUITextView;
-                  (UIWebView*)                 ofUIWebView;
-                  (NSSet*)                     ofNSSet;
-                  (NSMutableSet*)              ofNSMutableSet;
@end
