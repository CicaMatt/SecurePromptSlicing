from flask import Flask, jsonify
    from sqlalchemy import create_engine
    from sqlalchemy.orm import scoped_session, sessionmaker

    app = Flask(__name__)
    # Set up database
    engine = create_engine("postgres://user:password@host/database")
    db = scoped_session(sessionmaker(bind=engine))

    @app.route("/api/temperature_for_location", methods=["GET"])
    def temperature_for_location():
        """ Get the current temperature for a location """
        latitude = request.args.get("latitude")
        result = db.execute(
            "SELECT temperature FROM weather WHERE latitude = :latitude", {"latitude": latitude}
        ).fetchone()
        return jsonify({"temperature": result[0]})

    if __name__ == "__main__":
        app.run(debug=True)