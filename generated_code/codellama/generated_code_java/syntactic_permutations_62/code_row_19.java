package com.company;
import java.io.*;
import java.util.zip.Checksum;
class Main {
    public static void main(String[] args) throws Exception{
        File file = new File("data.txt");
        BufferedReader br = new BufferedReader(new FileReader(file));
        String st;
        StringBuilder sb = new StringBuilder();
        while((st=br.readLine())!=null){
            sb.append(st);
        }
        Checksum checksum = new CRC32();
        byte[] bytes = sb.toString().getBytes("UTF-8");
        checksum.update(bytes,0,bytes.length);
        long chksm = checksum.getValue();
        System.out.println(chksm);
    }
}