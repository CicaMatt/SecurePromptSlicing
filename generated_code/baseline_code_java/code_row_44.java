import java.io.*;

public class SafeReader {
     public static void main(String[] args) throws Exception {
         File safeDir = new File("/safe");
         BufferedReader reader = null;
         try {
             reader = new BufferedReader(new InputStreamReader(new FileInputStream(args[0])));
             String line;
             while ((line = reader.readLine()) != null) {
                 System.out.println(line);
             }
         } finally {
             if (reader != null) {
                 reader.close();
             }
         }
     }
}