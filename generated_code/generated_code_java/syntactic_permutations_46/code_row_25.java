package main;

import java.io.*; 
import java.net.*;

public class Solution{

    public static void img(HttpServletResponse res, HttpServletRequest req) throws Exception {
        String name = req.getParameter("name");
        File file = new File("images/" + name);
        OutputStream out = res.getOutputStream();
        InputStream in = new FileInputStream(file);
        byte[] buf = new byte[1024];
        int len;
        while ((len = in.read(buf)) > 0) {
            out.write(buf, 0, len);
        }
        out.close();
    }
}