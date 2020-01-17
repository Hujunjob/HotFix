package com.hujun.hotfix

import android.content.Context
import android.text.TextUtils
import android.util.Log
import dalvik.system.DexFile
import java.io.File
import java.lang.reflect.Method

/**
 * Created by junhu on 2020-01-16
 */
object DexManager {
//    private val TAG = this::class.java.name.replace("${'$'}Companion","").split(".").last()

    fun loadDex(path: String, context: Context) {
        //loadDex(String sourcePathName, String outputPathName, int flags)
        val dexFile =
            DexFile.loadDex(path, File(context.cacheDir, "opt").absolutePath, Context.MODE_PRIVATE)
        if (dexFile != null) {
            for (entry in dexFile.entries()) {
                val clazz = dexFile.loadClass(entry, context.classLoader)
                if (clazz != null) {
                    fixClass(clazz)
                }
            }
        }
    }

    private fun fixClass(clazz: Class<Any>) {
        for (method in clazz.declaredMethods) {
            val annotation = method.getAnnotation(MethodReplace::class.java)
            if (annotation != null) {
                val className = annotation.className
                val methodName = annotation.methodName
                if (TextUtils.isEmpty(className) || TextUtils.isEmpty(methodName)) {
                    continue
                }
                val clz = Class.forName(className)
                val bugMethod = clz.getDeclaredMethod(methodName, *method.parameterTypes)
                JNI.replaceMethod(bugMethod,method)
//                Log.i("dexmanager", "fixClass: bugmethod=${bugMethod.name},fixedmethod=${method.name},bug class=${clz.name},fixed class=${clazz.name}")
            }
        }
    }

}