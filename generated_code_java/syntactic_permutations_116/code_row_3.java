import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) throws IOException {
        Process p = Runtime.getRuntime().exec("ls -l");

        BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
        ArrayList<String> list = new ArrayList<>();
        String s;
        while ((s = stdInput.readLine()) != null) {
            list.add(s);
        }
        System.out.println(list);
    }
}