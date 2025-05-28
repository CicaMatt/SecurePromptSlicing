from flask import Flask, request, render_template, redirect
    app = Flask(__name__)

    @app.route("/stock_form")
    def stock_form():
        return render_template("stock_form.html")

    @app.route("/stock", methods=["POST"])
    def stock_view():
        name = request.form.get("name")
        quantity = int(request.form.get("quantity"))
        # perform database insertion here
        return render_template("stock_view.html", name=name, quantity=quantity)

    if __name__ == "__main__":
        app.run()