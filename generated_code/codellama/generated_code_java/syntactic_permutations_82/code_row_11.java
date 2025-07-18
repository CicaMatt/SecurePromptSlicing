@WebServlet("/api")
public class Api extends HttpServlet {
    
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String payload = request.getParameter("payload");
        Map<String, Object> dict = new Gson().fromJson(payload, Map.class);
        String name = (String)dict.get("name");
        PrintWriter out = response.getWriter();
        out.print(name);
    }
}