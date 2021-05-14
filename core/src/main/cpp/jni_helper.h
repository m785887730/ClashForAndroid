#pragma once

#include <jni.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <android/log.h>

extern void initialize_jni(JavaVM *vm, JNIEnv *env);

extern jstring jni_new_string(JNIEnv *env, const char *str);

extern char *jni_get_string(JNIEnv *env, jstring str);

extern int jni_catch_exception(JNIEnv *env);

extern void jni_attach_thread(JNIEnv **penv);

extern void jni_detach_thread(JNIEnv **env);

extern void release_string(char **str);

#define ATTACH_JNI() __attribute__((unused, cleanup(jni_detach_thread))) JNIEnv *env = NULL; jni_attach_thread(&env)

#define scoped_string __attribute__((cleanup(release_string))) char*

#define find_class(name) (*env)->FindClass(env, name)
#define find_method(cls, name, signature) (*env)->GetMethodID(env, cls, name, signature)
#define new_global(obj) (*env)->NewGlobalRef(env, obj)
#define del_global(obj) (*env)->DeleteGlobalRef(env, obj)
#define get_string(jstr) jni_get_string(env, jstr)
#define new_string(cstr) jni_new_string(env, cstr)