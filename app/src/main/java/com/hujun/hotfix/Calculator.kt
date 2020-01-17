package com.hujun.hotfix

import android.content.Context
import android.view.Surface
import android.view.SurfaceView
import android.widget.Toast

/**
 * Created by junhu on 2020-01-03
 */
class Calculator {
    fun calculator(context: Context) {
        val a = 100
        val b = 0
        Toast.makeText(context, "calculator a/b = ${a / b}", Toast.LENGTH_SHORT).show()
    }
}
