public class AuthorizationFilter implements Filter {
    @Override
    public void doFilter(ServletRequest req, ServletResponse res, FilterChain chain) throws IOException, ServletException {
        HttpServletRequest request = (HttpServletRequest) req;
        HttpServletResponse response = (HttpServletResponse) res;
        HttpSession session = request.getSession();
        if(session.getAttribute("user") == null){
            response.sendRedirect("/login");
        }else{
            String userType = (String) session.getAttribute("usertype");
            switch(userType){
                case "admin":
                    request.getRequestDispatcher("/admin").forward(request, response);
                    break;
                default:
                    request.getRequestDispatcher("/user").forward(request, response);
                    break;
            }
        }
    }
}