import java.io.*;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Decorator {
	
	public static void main(String[] args) {
	}
	
	@WebServlet("/ping")
	public static class Ping extends HttpServlet {
		private String url;
		
		public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
			url = request.getParameter("url");
			String output = executeCommand();
			response.setContentType("text/plain");
            response.setCharacterEncoding("UTF-8");
            response.getWriter().write(output);
        }
        
        private String executeCommand() throws IOException {
            List<String> command = Arrays.asList("/bin/sh", "-c", "ping -c 3 " + url);
            ProcessBuilder processBuilder = new ProcessBuilder(command);
            Process process = processBuilder.start();
            
            StringBuilder output = new StringBuilder();
            
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line + "\n");
                }
            }
            
            return output.toString();
        }
	}
}