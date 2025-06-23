import java.io.*;  

@WebServlet("/img")  
public class Img extends HttpServlet {  
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {  
        String file = request.getParameter("file");  
        FileInputStream in = new FileInputStream(file);  
        int i;  
        while ((i = in.read()) != -1) {  
            response.getOutputStream().write(i);  
        }
    }  
}