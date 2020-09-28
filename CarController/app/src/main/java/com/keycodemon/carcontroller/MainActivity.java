package com.keycodemon.carcontroller;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Spinner;
import android.widget.Toast;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Set;

public class MainActivity extends AppCompatActivity implements View.OnClickListener, View.OnTouchListener {

    Spinner spnDeviceList;
    Button btnConnectBT, btnForward, btnBackward, btnForwardLeft, btnForwardRight, btnBackwardLeft, btnBackwardRight;
    ImageButton btn;

    private ConnectBT connectBT = null;
    private BluetoothAdapter bluetoothAdapter = null;
    private BluetoothSocket bluetoothSocket = null;
    private Set<BluetoothDevice> pairedDevices;

    private String bluetoothAddress;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Init();
    }

    void Init(){
        InitView();
        InitBluetooth();
    }

    void InitView(){

        spnDeviceList = findViewById(R.id.spnDeviceList);
        btnConnectBT = findViewById(R.id.btnConnectBT);
        btnConnectBT.setOnClickListener(this);

        btnForward = findViewById(R.id.btnForward);
        btnBackward = findViewById(R.id.btnBackward);
        btnForwardLeft = findViewById(R.id.btnForwardLeft);
        btnForwardRight = findViewById(R.id.btnForwardRight);
        btnBackwardLeft = findViewById(R.id.btnBackwardLeft);
        btnBackwardRight = findViewById(R.id.btnBackwardRight);
        btnForward.setOnTouchListener(this);
        btnBackward.setOnTouchListener(this);
        btnForwardLeft.setOnTouchListener(this);
        btnForwardRight.setOnTouchListener(this);
        btnBackwardLeft.setOnTouchListener(this);
        btnBackwardRight.setOnTouchListener(this);

    }

    void InitBluetooth(){

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if(bluetoothAdapter == null){
            Toast.makeText(getApplicationContext(), "Bluetooth Device Not Available", Toast.LENGTH_LONG).show();
            finish();
        }else if(!bluetoothAdapter.isEnabled()){
            Intent turnOnBT = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(turnOnBT, 1);
        }

        ShowDeviceList();
    }

    void ShowDeviceList(){
        pairedDevices = bluetoothAdapter.getBondedDevices();
        ArrayList deviceList = new ArrayList();

        if(pairedDevices.size()>0){
            for(BluetoothDevice bt:pairedDevices){
                deviceList.add(bt.getName() + "\n" + bt.getAddress());
            }
        }else{
            Toast.makeText(getApplicationContext(), "No paired bluetooth devices found", Toast.LENGTH_LONG).show();
        }

        final ArrayAdapter<String> deviceListAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, deviceList);
        deviceListAdapter.setDropDownViewResource(android.R.layout.simple_list_item_single_choice);
        spnDeviceList.setAdapter(deviceListAdapter);
    }

    void SendCommandToArduino(String command){
        if(bluetoothSocket != null){
            try{
                bluetoothSocket.getOutputStream().write(command.getBytes());
            }catch (IOException e){
                Toast.makeText(getApplicationContext(), "Error", Toast.LENGTH_LONG).show();
            }
        }else{
            Toast.makeText(getApplicationContext(), "You did not connect to bluetooth device!", Toast.LENGTH_LONG).show();
        }
    }

    void ConnectBluetoothDevice(Button btnConnect){
        if(btnConnect.getText().equals("Connect")){
            String deviceInfo = spnDeviceList.getSelectedItem().toString();
            bluetoothAddress = deviceInfo.substring(deviceInfo.length() - 17);
            connectBT = (ConnectBT) new ConnectBT(getApplicationContext(), bluetoothAdapter, bluetoothAddress).execute();
            while (bluetoothSocket==null){
                bluetoothSocket = connectBT.getBluetoothSocket();
            }
            btnConnect.setText("Disconnect");
        }else{
            if(bluetoothSocket != null){
                try {
                    bluetoothSocket.close();
                    bluetoothSocket = null;
                    Toast.makeText(getApplicationContext(), "Disconnect successful!", Toast.LENGTH_LONG).show();
                    btnConnect.setText("Connect");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }else{
                Toast.makeText(getApplicationContext(), "Bluetooth Socket is null", Toast.LENGTH_LONG).show();
            }
        }
    }

    @Override
    public void onClick(View view) {

        switch(view.getId()){
            case R.id.btnConnectBT:
                Button btnConnect = (Button) view;
                ConnectBluetoothDevice(btnConnect);
                break;
            default:
                break;
        }

    }

    @Override
    public boolean onTouch(View view, MotionEvent motionEvent) {

        if(motionEvent.getAction() == MotionEvent.ACTION_DOWN){
            switch (view.getId()){
                case R.id.btnForward:
                    SendCommandToArduino("1");
                    break;
                case R.id.btnBackward:
                    SendCommandToArduino("2");
                    break;
                case R.id.btnForwardLeft:
                    SendCommandToArduino("3");
                    break;
                case R.id.btnForwardRight:
                    SendCommandToArduino("4");
                    break;
                case R.id.btnBackwardLeft:
                    SendCommandToArduino("5");
                    break;
                case R.id.btnBackwardRight:
                    SendCommandToArduino("6");
                    break;
            }
        }else if(motionEvent.getAction() == MotionEvent.ACTION_UP){
            SendCommandToArduino("0");
        }

        return false;
    }
}