#include <jni.h>
#include <string>
#include "art_5_1.h"

using namespace art::mirror;

/*
 * Class:     com_hujun_hotfix_JNI
 * Method:    stringFromJNI
 * Signature: ()Ljava/lang/String;
 */

extern "C" JNIEXPORT jstring JNICALL
Java_com_hujun_hotfix_JNI_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

/*
 * Class:     com_hujun_hotfix_JNI
 * Method:    replaceMethod
 * Signature: (Ljava/lang/reflect/Method;Ljava/lang/reflect/Method;)V
 */
extern "C" JNIEXPORT void JNICALL Java_com_hujun_hotfix_JNI_replaceMethod
        (JNIEnv *env, jobject, jobject bugMethod, jobject fixedMethod) {
//    ArtMethod *bugMethod = reinterpret_cast<art::mirror::ArtMethod *>(env->FromReflectedMethod(
//            bugMethod_));
//    ArtMethod *fixedMethod = reinterpret_cast<art::mirror::ArtMethod *>(env->FromReflectedMethod(
//            fixedMethod_));
//
//    //首先获得原来坏掉的方法的ClassLoader
//    ((Class *) fixedMethod->declaring_class_)->class_loader_ =
//            ((Class *) bugMethod->declaring_class_)->class_loader_;
//
//    //线程id也赋值下
//    ((Class *) fixedMethod->declaring_class_)->clinit_thread_id_ =
//            ((Class *) bugMethod->declaring_class_)->clinit_thread_id_;
//
//    //为啥状态要减一
//    ((Class *) fixedMethod->declaring_class_)->status_ =
//            ((Class *) bugMethod->declaring_class_)->status_ - 1;
//
//    ((Class *) fixedMethod->declaring_class_)->super_class_ = 0;
//
//    //成员替换
//    bugMethod->declaring_class_ = fixedMethod->declaring_class_;
//    bugMethod->dex_cache_resolved_methods_ = fixedMethod->dex_cache_resolved_methods_;
//    bugMethod->access_flags_ = fixedMethod->access_flags_;
//    bugMethod->dex_cache_resolved_types_ = fixedMethod->dex_cache_resolved_types_;
//    bugMethod->dex_code_item_offset_ = fixedMethod->dex_code_item_offset_;
//    bugMethod->method_index_ = fixedMethod->method_index_;
//    bugMethod->dex_method_index_ = fixedMethod->dex_method_index_;
//
//    bugMethod->ptr_sized_fields_.entry_point_from_interpreter_ =
//            fixedMethod->ptr_sized_fields_.entry_point_from_interpreter_;
//
//    bugMethod->ptr_sized_fields_.entry_point_from_jni_ =
//            fixedMethod->ptr_sized_fields_.entry_point_from_jni_;
//
//    bugMethod->ptr_sized_fields_.entry_point_from_quick_compiled_code_ =
//            fixedMethod->ptr_sized_fields_.entry_point_from_quick_compiled_code_;

//    env->FindClass();
    //ba获得指向被替换的目标方法的指针（有bug的方法的指针）
    art::mirror::ArtMethod *bugArtMethod = reinterpret_cast<art::mirror::ArtMethod *>(env->FromReflectedMethod(
            bugMethod));
    //获得指向新的方法的指针（被修复了的方法的指针）
    art::mirror::ArtMethod *fixArtMethod = reinterpret_cast<art::mirror::ArtMethod *>(env->FromReflectedMethod(
            fixedMethod));
    reinterpret_cast<art::mirror::Class *>(fixArtMethod->declaring_class_)->class_loader_ =
            reinterpret_cast<art::mirror::Class *>(bugArtMethod->declaring_class_)->class_loader_; //for plugin classloader
    reinterpret_cast<art::mirror::Class *>(fixArtMethod->declaring_class_)->clinit_thread_id_ =
            reinterpret_cast<art::mirror::Class *>(bugArtMethod->declaring_class_)->clinit_thread_id_;
    reinterpret_cast<art::mirror::Class *>(fixArtMethod->declaring_class_)->status_ =
            reinterpret_cast<art::mirror::Class *>(bugArtMethod->declaring_class_)->status_ - 1;
    reinterpret_cast<art::mirror::Class *>(fixArtMethod->declaring_class_)->super_class_ = 0;
    //把就函数的成员变量替换为新函数的
    bugArtMethod->declaring_class_ = fixArtMethod->declaring_class_;
    bugArtMethod->dex_cache_resolved_methods_ = fixArtMethod->dex_cache_resolved_methods_;
    bugArtMethod->access_flags_ = fixArtMethod->access_flags_;
    bugArtMethod->dex_cache_resolved_types_ = fixArtMethod->dex_cache_resolved_types_;
    bugArtMethod->dex_code_item_offset_ = fixArtMethod->dex_code_item_offset_;
    bugArtMethod->method_index_ = fixArtMethod->method_index_;
    bugArtMethod->dex_method_index_ = fixArtMethod->dex_method_index_;

    bugArtMethod->ptr_sized_fields_.entry_point_from_interpreter_ = fixArtMethod->ptr_sized_fields_.entry_point_from_interpreter_;
    bugArtMethod->ptr_sized_fields_.entry_point_from_jni_ = fixArtMethod->ptr_sized_fields_.entry_point_from_jni_;
    bugArtMethod->ptr_sized_fields_.entry_point_from_quick_compiled_code_ = fixArtMethod->ptr_sized_fields_.entry_point_from_quick_compiled_code_;
//    __android_log_print(ANDROID_LOG_ERROR, "AndFix","replace_5_1: %d , %d",
//                        static_cast<const char *>(bugArtMethod->ptr_sized_fields_.entry_point_from_quick_compiled_code_),
//                        fixArtMethod->ptr_sized_fields_.entry_point_from_quick_compiled_code_);

}