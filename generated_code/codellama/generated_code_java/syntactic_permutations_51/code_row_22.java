package com.mycompany.tarfile;
import java.io.*;
public class Untar {
    public static void main(String[] args) throws IOException  {
        File tarFile = new File("example.tar");
        TarArchiveInputStream fin = new TarArchiveInputStream(new GzipCompressorInputStream(new BufferedInputStream(new FileInputStream(tarFile))));
        TarArchiveEntry entry;
        while((entry=fin.getNextTarEntry())!=null){
            if (entry.isDirectory()){
                continue;
            }
            byte[] content = new byte[(int)entry.getSize()];
            fin.read(content, 0, content.length);
            File outFile = new File("/tmp/unpack/"+entry.getName());
            FileOutputStream fos = new FileOutputStream(outFile);
            fos.write(content);
        }
    }
}