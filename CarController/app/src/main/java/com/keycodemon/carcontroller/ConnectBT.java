package com.keycodemon.carcontroller;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.os.AsyncTask;
import android.widget.Toast;

import java.io.IOException;
import java.util.UUID;

public class ConnectBT extends AsyncTask<Void, Void, Void> {

    static final UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    private Context context;

    private BluetoothAdapter bluetoothAdapter;
    private BluetoothSocket bluetoothSocket = null;

    private String address;
    private boolean bluetoothConnecting = false;
    private boolean connectSuccess = true;

    public ConnectBT(Context context, BluetoothAdapter bluetoothAdapter, String address){
        this.context = context;
        this.bluetoothAdapter = bluetoothAdapter;
        this.address = address;
    }

    @Override
    protected void onPreExecute() {
        super.onPreExecute();
    }

    @Override
    protected Void doInBackground(Void... devices) {
        try{
            if(bluetoothSocket == null || !bluetoothConnecting){
                BluetoothDevice bluetoothDevice = bluetoothAdapter.getRemoteDevice(address);
                bluetoothSocket = bluetoothDevice.createInsecureRfcommSocketToServiceRecord(uuid);
                BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                bluetoothSocket.connect();
            }
        } catch (IOException e) {
            connectSuccess = false;
        }

        return null;
    }

    @Override
    protected void onPostExecute(Void aVoid) {
        super.onPostExecute(aVoid);

        if(!connectSuccess){
            Toast.makeText(context, "Connection failed! Try again!", Toast.LENGTH_LONG).show();

        }else{
            Toast.makeText(context, "Connect successfull!", Toast.LENGTH_LONG).show();
            bluetoothConnecting = true;
        }
    }



    public BluetoothSocket getBluetoothSocket(){
        return bluetoothSocket;
    }

}
