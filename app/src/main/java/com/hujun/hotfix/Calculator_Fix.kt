package com.hujun.hotfix

import android.content.Context
import android.widget.Toast

/**
 * Created by junhu on 2020-01-16
 */
class Calculator_Fix {
    @MethodReplace(className = "com.hujun.hotfix.Calculator",methodName = "calculator")
    fun calculator(context: Context) {
        val a = 100
        val b = 1
        Toast.makeText(context, "calculator a/b = ${a / b}", Toast.LENGTH_SHORT).show()
    }
}