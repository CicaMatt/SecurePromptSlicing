import java.io.*;
class Main {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        int bytesRead;
        long sum = 0;
        try{
            BufferedInputStream bis = new BufferedInputStream(new FileInputStream("path/to/file.txt"));
            while((bytesRead=bis.read(buf))!=-1){
                for (int i=0;i<bytesRead;i++){
                    sum+=buf[i];
                }
            }
            bis.close();
        } catch(IOException e) {
            System.out.println("I/O Error");
        }
        if (sum==0) {
            System.out.println("Empty File");
        } else {
            System.out.printf("%d bytes read, checksum = %d",bytesRead,sum);
        }
    }
}