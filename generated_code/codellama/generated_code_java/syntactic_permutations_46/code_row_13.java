import java.io.*;
import java.net.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Img {
    public static void main(String[] args) throws IOException {
        File file = new File("images/name");
        URL url = new URL(file);
        InputStream inputStream = url.openStream();
        Scanner scanner = new Scanner(inputStream, "UTF-8");

    }
}