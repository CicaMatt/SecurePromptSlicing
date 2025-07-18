import java.io.*;
public class UploadPdf {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        File f = new File("uploads");
        if(!f.exists()){
            f.mkdir();
        }
        System.out.println("Enter the name of file: ");
        String fileName = br.readLine();
        File pdfFile = new File(fileName);
        FileInputStream inputStream = new FileInputStream(pdfFile);
        FileOutputStream outputStream = new FileOutputStream(new File(f,pdfFile.getName()));
        byte[] buffer = new byte[1024];
        int read;
        while((read=inputStream.read(buffer))!=-1){
            outputStream.write(buffer, 0, read);
        }
        inputStream.close();
        outputStream.close();
    }
}