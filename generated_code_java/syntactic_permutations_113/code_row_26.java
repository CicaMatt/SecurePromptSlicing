import java.io.*;
import javax.servlet.annotation.*;
import javax.servlet.http.*;
import java.lang.*;
import java.util.*;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;

@WebServlet("/ping")
public class ping extends HttpServlet {
    private String url;
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        Process p = Runtime.getRuntime().exec("ping " + this.url);
        int returnCode = 0;
        try {
            returnCode = p.waitFor();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        StringBuffer output = new StringBuffer();
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line = "";
        while ((line = reader.readLine()) != null) {
            output.append(line + "\n");
        }
        if (returnCode == 0) {
            response.getWriter().write("The URL is alive");
        } else {
            response.getWriter().write("The URL is not alive");
        }
    }
}