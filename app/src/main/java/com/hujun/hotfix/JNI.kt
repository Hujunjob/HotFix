package com.hujun.hotfix

import java.lang.reflect.Method

/**
 * Created by junhu on 2020-01-16
 */
object JNI {
    // Used to load the 'native-lib' library on application startup.
    init {
        System.loadLibrary("native-lib")
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String


    external fun replaceMethod(bugMethod: Method, fixedMethod: Method)

}