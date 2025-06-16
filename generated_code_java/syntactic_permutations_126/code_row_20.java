import java.io.*;

public class HelloWorld {
    public static void main(String[] args) throws Exception{
        String output = "Hello World";
        HttpServletRequest request = null;
        HttpServletResponse response = null;
        try{
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println(output);
        }catch(Exception e){
            System.out.println(e);
        }finally{
            if (response != null) {
                response.flushBuffer();
            }
        }
    }
}