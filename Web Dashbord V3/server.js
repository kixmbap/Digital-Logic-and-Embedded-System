const express = require("express");
const { SerialPort } = require("serialport");

const app = express();


// =====================================================
// CONFIG
// =====================================================

const PORT = 3000;

const SERIAL_PORT = "COM7";

const BAUD_RATE = 9600;


// =====================================================
// STATE
// =====================================================

let state = {

    door1: "CLOSED",

    door2: "CLOSED",

    door3: "CLOSED",

    door4: "CLOSED",

    door5: "CLOSED",

    laser1: "NOT_DETECTED",

    laser2: "NOT_DETECTED",

    switch1: "OFF",

    switch2: "OFF",

    system: "READY"

};


// =====================================================
// SERIAL LOG
// =====================================================

let messages = [];


// =====================================================
// WEB SERVER
// =====================================================

// เปิดไฟล์ index.html
app.use(express.static(__dirname));


// =====================================================
// API
// =====================================================

// เว็บเรียก API นี้เพื่อเอาข้อมูล Arduino
app.get("/api/state", (req, res) => {

    res.json({

        state: state,

        messages: messages

    });

});

// ส่งคำสั่งรีเซ็ตไปยัง Arduino และเคลียร์สถานะเซิร์ฟเวอร์
app.post("/api/reset", (req, res) => {
    console.log("Sending Reset command 'R' to Arduino...");

    // รีเซ็ตสถานะฝั่งเซิร์ฟเวอร์ก่อน
    state = {
        door1: "CLOSED",
        door2: "CLOSED",
        door3: "CLOSED",
        door4: "CLOSED",
        door5: "CLOSED",
        laser1: "NOT_DETECTED",
        laser2: "NOT_DETECTED",
        switch1: "OFF",
        switch2: "OFF",
        system: "READY"
    };
    messages = [];

    // ส่งสัญญาณ 'R' ไปยังบอร์ด Arduino
    serial.write("R", (err) => {
        if (err) {
            console.error("Error writing reset to Serial:", err);
            return res.status(500).json({ success: false, error: err.message });
        }
        res.json({ success: true, message: "Reset command sent to Arduino successfully" });
    });
});

// =====================================================
// START WEB SERVER
// =====================================================

app.listen(PORT, () => {

    console.log("");

    console.log("================================");

    console.log("       ROBOT FIELD SERVER");

    console.log("================================");

    console.log(`Web: http://localhost:${PORT}`);

    console.log(`Serial: ${SERIAL_PORT}`);

    console.log(`Baud Rate: ${BAUD_RATE}`);

    console.log("================================");

    console.log("");

});


// =====================================================
// CONNECT TO ARDUINO
// =====================================================

const serial = new SerialPort({

    path: SERIAL_PORT,

    baudRate: BAUD_RATE

});


// =====================================================
// SERIAL BUFFER
// =====================================================

// สำคัญมาก
// ใช้เก็บข้อมูลกรณี Arduino ส่งมาไม่ครบทีเดียว

let serialBuffer = "";


// =====================================================
// SERIAL OPEN
// =====================================================

serial.on("open", () => {

    console.log(
        `Arduino connected: ${SERIAL_PORT}`
    );

});


// =====================================================
// RECEIVE DATA FROM ARDUINO
// =====================================================

serial.on("data", (data) => {

    // ---------------------------------------------
    // เอาข้อมูลใหม่มาต่อกับ buffer เดิม
    // ---------------------------------------------

    serialBuffer += data.toString();


    // ---------------------------------------------
    // แยกข้อมูลตาม \n
    // ---------------------------------------------

    const lines =
        serialBuffer.split(/\r?\n/);


    // ---------------------------------------------
    // ตัวสุดท้ายอาจยังอ่านไม่ครบ
    // เก็บไว้รอบถัดไป
    // ---------------------------------------------

    serialBuffer = lines.pop();


    // ---------------------------------------------
    // ประมวลผลแต่ละบรรทัด
    // ---------------------------------------------

    lines.forEach(line => {

        const message = line.trim();


        // ถ้าเป็นบรรทัดว่างไม่ต้องทำอะไร
        if (message === "") {

            return;

        }


        // -----------------------------------------
        // แสดงใน CMD
        // -----------------------------------------

        console.log(
            "Arduino:",
            message
        );


        // -----------------------------------------
        // เก็บ Log
        // -----------------------------------------

        messages.push(message);


        // เก็บสูงสุด 100 ข้อความ
        if (messages.length > 100) {

            messages.shift();

        }


        // -----------------------------------------
        // วิเคราะห์ข้อความ
        // -----------------------------------------

        processMessage(message);

    });

});


// =====================================================
// PROCESS ARDUINO MESSAGE
// =====================================================

function processMessage(message) {


    // =================================================
    // DOOR 1
    // =================================================

    if (message === "DOOR 1 -> OPEN") {

        state.door1 = "OPEN";

    }


    if (message === "DOOR 1 -> CLOSED") {

        state.door1 = "CLOSED";

    }


    // =================================================
    // DOOR 2
    // =================================================

    if (message === "DOOR 2 -> OPEN") {

        state.door2 = "OPEN";

    }


    if (message === "DOOR 2 -> CLOSED") {

        state.door2 = "CLOSED";

    }


    if (message === "DOOR 2 -> LOCKED") {

        state.door2 = "CLOSED";

    }


    // =================================================
    // DOOR 3
    // =================================================

    if (message === "DOOR 3 -> OPEN") {

        state.door3 = "OPEN";

    }


    if (message === "DOOR 3 -> CLOSED") {

        state.door3 = "CLOSED";

    }


    if (message === "DOOR 3 -> LOCKED") {

        state.door3 = "CLOSED";

    }


    // =================================================
    // DOOR 4
    // =================================================

    if (message === "DOOR 4 -> OPEN") {

        state.door4 = "OPEN";

    }


    if (message === "DOOR 4 -> CLOSED") {

        state.door4 = "CLOSED";

    }


    // =================================================
    // DOOR 5
    // =================================================

    if (message === "DOOR 5 -> OPEN") {

        state.door5 = "OPEN";

    }


    if (message === "DOOR 5 -> CLOSED") {

        state.door5 = "CLOSED";

    }


    if (message === "DOOR 5 -> LOCKED") {

        state.door5 = "CLOSED";

    }


    // =================================================
    // LASER 1
    // =================================================

    if (message === "LASER 1 DETECTED") {

        state.laser1 = "DETECTED";

    }


    if (message === "LASER 1 LOST") {

        state.laser1 = "NOT_DETECTED";

    }


    // =================================================
    // LASER 2
    // =================================================

    if (message === "LASER 2 DETECTED") {

        state.laser2 = "DETECTED";

    }


    if (message === "LASER 2 LOST") {

        state.laser2 = "NOT_DETECTED";

    }


    // =================================================
    // SWITCH 1
    // =================================================

    if (message === "SWITCH 1") {

        state.switch1 = "ON";

    }


    // =================================================
    // SWITCH 2
    // =================================================

    if (message === "SWITCH 2") {

        state.switch2 = "ON";

    }


    // =================================================
    // SYSTEM
    // =================================================

    if (message === "System Ready") {

        state.system = "READY";

    }

}


// =====================================================
// SERIAL ERROR
// =====================================================

serial.on("error", (err) => {

    console.log("");

    console.log("================================");

    console.log("SERIAL ERROR");

    console.log("================================");

    console.log(err.message);

    console.log("");

});