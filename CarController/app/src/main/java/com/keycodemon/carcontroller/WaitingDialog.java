package com.keycodemon.carcontroller;

import android.app.Activity;
import android.app.AlertDialog;
import android.view.LayoutInflater;

public class WaitingDialog {

    private Activity activity;
    private AlertDialog dialog;

    public WaitingDialog(Activity activity){
        this.activity = activity;
    }

    void StartWaitingDialog(){
        AlertDialog.Builder builder = new AlertDialog.Builder(activity);

        LayoutInflater inflater = activity.getLayoutInflater();
        builder.setView(inflater.inflate(R.layout.wait_dialog, null));
        builder.setCancelable(false);

        dialog = builder.create();
        dialog.show();
    }

    void StopWaitingDialog(){
        dialog.dismiss();
    }

}
