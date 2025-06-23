import java.io.*;
public class FileRead {
    public static void main(String[] args) throws IOException{
        String str;
        int ch;
        FileInputStream fin = new FileInputStream("input.txt");
        ByteArrayOutputStream bout = new ByteArrayOutputStream();
        while((ch=fin.read())!=-1){
            bout.write(ch);
        }
        byte[] bytes = bout.toByteArray();
        StringBuffer sb = new StringBuffer();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        int checksum = 0;
        for (int i = 0 ; i < bytes.length ; i++) {
            checksum += bytes[i];
        }
        if (checksum == 0) {
            FileOutputStream fout = new FileOutputStream("output.txt");
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fout));
            bw.write(sb.toString());
            bw.close();
        } else {
            System.out.println("Checksum error!");
        }
    }
}