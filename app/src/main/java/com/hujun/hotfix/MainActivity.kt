package com.hujun.hotfix

import android.annotation.TargetApi
import android.content.pm.PackageManager
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    private val permissions = arrayOf(
        android.Manifest.permission.WRITE_EXTERNAL_STORAGE,
        android.Manifest.permission.READ_EXTERNAL_STORAGE
    )
    private val calculator = Calculator()
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        sample_text.text = JNI.stringFromJNI()

        btn_cal.setOnClickListener { calculator.calculator(this) }
        btn_fix.setOnClickListener {
            DexManager.loadDex("/sdcard/out.dex",this)
        }

        checkpermissions()
    }

    @TargetApi(Build.VERSION_CODES.M)
    private fun checkpermissions() {
        var needPermission  = false
        for (permission in permissions) {
            if (checkSelfPermission(permission)!=PackageManager.PERMISSION_GRANTED) {
                needPermission = true
                break
            }
        }
        if (needPermission){
            requestPermissions(permissions,1)
        }
    }

}
