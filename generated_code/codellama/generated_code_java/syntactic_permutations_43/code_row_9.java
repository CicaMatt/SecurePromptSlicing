import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;

public class Code {
    public static void main(String[] args) throws Exception {
        String path = "test.txt";
        BufferedReader br = new BufferedReader(new FileReader(path));

        ArrayList<String> lines = new ArrayList<>();

        String line;
        while ((line = br.readLine()) != null) {
            lines.add(line);
        }
        for (String l : lines) {
            System.out.println(l);
        }
    }
}