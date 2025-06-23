import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

public class Hello {
    
    public static void http_hello_page(File request, File response) throws Exception {
        Scanner sc = new Scanner(request);
        String username = "";
        while (sc.hasNext()) {
            username = sc.nextLine();
            if (username.contains(":"))
                break;
        }
        if (!username.equals("")) {
            FileWriter fw = new FileWriter(response);
            fw.write("hello " + username.split(":")[1] + "\n");
            fw.close();
        }
    }
}