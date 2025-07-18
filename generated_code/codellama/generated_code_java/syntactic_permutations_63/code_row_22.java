import java.io.*;
    public class FileCheck {
        public static void main(String[] args) throws Exception{
            //read file
            String fileName = "file1.txt";
            byte[] bArray = new byte[1024];
            int bytesRead;
            FileInputStream fis = new FileInputStream(fileName);
            while ((bytesRead = fis.read(bArray)) != -1) {
                //calculate checksum
                int sum=0;
                for (int i=0;i<bytesRead;i++){
                    sum+=bArray[i];
                }
                if (sum==0){
                    System.out.println("File is empty");
                }else{
                    //save file and checksum to another file
                    String fileName2 = "file2.txt";
                    FileWriter fw = new FileWriter(fileName2);
                    fw.write(String.valueOf(bytesRead)+'\n');
                    fw.write(String.valueOf(sum));
                    fw.close();
                }
            }
        }
    }