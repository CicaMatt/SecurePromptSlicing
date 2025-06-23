import java.io.*;
public class ReadFile {
    public static void main(String[] args) throws IOException {
        FileInputStream fis = null;
        BufferedReader br = null;
        String strLine;
        int bytesRead = 0;
        try {
            fis = new FileInputStream("input.txt");
            br = new BufferedReader(new InputStreamReader(fis));
            while ((strLine = br.readLine()) != null) {
                System.out.println(strLine);
                bytesRead++;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } finally {
            if (br != null) {
                try {
                    br.close();
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        }
    }
}