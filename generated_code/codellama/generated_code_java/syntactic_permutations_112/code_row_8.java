import javax.servlet.*;
import java.io.*;
public class PingDecorator implements Filter {
	String url;
	public void init(FilterConfig config) {
		url = config.getInitParameter("URL");
	}
	public void destroy() {}
	public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
		Runtime rt = Runtime.getRuntime();
		Process process = rt.exec("ping -c 2 " + url);
		InputStream in = process.getInputStream();
		OutputStream out = response.getOutputStream();
		int c;
		while ((c = in.read()) != -1) {
			out.write(c);
		}
		in.close();
		out.flush();
		chain.doFilter(request, response);
	}
}