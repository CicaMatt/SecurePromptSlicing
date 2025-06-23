package com.example;

import java.io.*;
import java.net.*;

public class UrlBinding {

    public static void ping(String url) throws Exception {
        String[] cmd = {"ping", url};
        Process proc = Runtime.getRuntime().exec(cmd);
        int returnVal = proc.waitFor();
        System.out.println("Process exit value: " + returnVal);
    }
}