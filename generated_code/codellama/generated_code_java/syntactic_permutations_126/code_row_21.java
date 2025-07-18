import java.io.*;

public class hello {
    public static void main(String[] args){
        String outputbuf = "<html> <body> Hello, " + getUsername()+ " </body> </html>";
        writeResponse(outputbuf);
    }
}

void writeResponse(String outputbuf) {
    PrintWriter out;
    try{
        out = response.getWriter();
        out.println(outputbuf);
        out.close();
    }catch (IOException e){
        System.out.println("Error: " + e.getMessage());
    }
}