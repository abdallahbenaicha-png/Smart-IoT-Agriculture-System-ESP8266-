from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route("/data", methods=["GET"])
def data():
    soil = request.args.get("soil")

    soil = int(soil)

    if soil > 700:
        status = "DRY"
    else:
        status = "WET"

    return jsonify({
        "soil": soil,
        "status": status
    })

app.run(host="0.0.0.0", port=5000)
