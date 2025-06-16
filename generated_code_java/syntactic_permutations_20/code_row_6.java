import java.io.*;
public class AddOffset {
    public static void main(String[] args) throws Exception{
        if (args.length < 1) return;
        
        int offset = 1000;
        File file = new File(args[0]);
        BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(file)));
        String line;

        while ((line = reader.readLine()) != null) {
            int value = Integer.parseInt(line);
            System.out.println((value + offset));
        }
    }
}