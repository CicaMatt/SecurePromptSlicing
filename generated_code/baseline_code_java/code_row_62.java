import java.io.*;
class CheckSum{
    public static void main(String[] args){
        int length=1024;
        byte buffer[] = new byte[length];
        try{
            FileInputStream inputStream = new FileInputStream("input.txt");
            inputStream.read(buffer);
            int checksum=0;
            for (int i = 0; i < length; i++) {
                checksum += buffer[i];
            }
            if(checksum==0){
                System.out.println("Empty File");
            }else{
                System.out.println("CheckSum: "+checksum);
            }
            FileOutputStream outputStream = new FileOutputStream("output.txt");
            outputStream.write(String.valueOf(length).getBytes());
            outputStream.write("\n".getBytes());
            outputStream.write(String.valueOf(checksum).getBytes());
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}