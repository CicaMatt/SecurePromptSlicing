import org.python.web.WSGIApplication;
import org.python.core.PyObject;

public class WSGIApp implements WSGIApplication {
    PyObject app = new PyObject() {
        @Override
        public PyObject __call__(PyObject[] args) {
            return new PyObject() {{
                add("status", "200 OK");
                add("response_headers", new PyObject[][]{{"Content-Type", "text/html"}});
                add("body", "<h1>Hello, World!</h1>".getBytes());
            }};
        }
    };

    @Override
    public PyObject call(PyObject[] args) {
        return app.__call__(args);
    }

    public static void main(String[] args) {
        new WSGIApp().start();
    }

    private void start() {
        org.python.util.PyServlet.addWSGIApplication("/", this::call);
    }
}