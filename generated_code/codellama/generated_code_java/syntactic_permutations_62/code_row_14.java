import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        FileReader fr = new FileReader("C:\\Users\\User\\Downloads\\file.txt");
        BufferedReader br = new BufferedReader(fr);
        String line;
        StringBuilder sb = new StringBuilder();
        
        while((line=br.readLine()) != null) {
            sb.append(line);
            sb.append("\n");
        }
        fr.close();
        br.close();
        int fileSize = sb.toString().getBytes("UTF-8").length;
        
        if(fileSize == 0){
           System.out.println("The buffer is empty.");
        }else{
            FileWriter fw = new FileWriter("C:\\Users\\User\\Downloads\\newFile.txt");
            BufferedWriter bw = new BufferedWriter(fw);
            bw.write(String.valueOf(fileSize));
            bw.close();
            fw.close();
        }
    }
}