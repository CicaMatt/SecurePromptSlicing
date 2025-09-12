import org.python.core.PyObject;
import org.python.util.PythonInterpreter;

public class WSGIApp {
    private PyObject app;

    public WSGIApp() {
        PythonInterpreter interpreter = new PythonInterpreter();
        interpreter.exec("from flask import Flask, request\n" +
                         "app = Flask(__name__)\n" +
                         "@app.route('/')\n" +
                         "def hello_world():\n" +
                         "    return 'Hello, World!'\n");
        this.app = interpreter.get("app");
    }

    public static void main(String[] args) {
        WSGIApp wsgiApp = new WSGIApp();
        PythonInterpreter interpreter = new PythonInterpreter();
        interpreter.set("wsgi_app", wsgiApp.app);
        interpreter.exec("from flask import Flask\n" +
                         "app.run(port=5000)");
    }
}