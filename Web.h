
const char PAGE_MAIN[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8" />
        <meta http-equiv="X-UA-Compatible" content="IE=edge" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0" />
        <title>Đồ Án Cơ Sở</title>
        <link rel="shortcut icon" href="led.png" type="image/x-icon" />
        <link
            href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css"
            rel="stylesheet"
            integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC"
            crossorigin="anonymous"
        />
        <script
            src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js"
            integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM"
            crossorigin="anonymous"
        ></script>
        <script
            src="https://code.jquery.com/jquery-3.6.0.min.js"
            integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4="
            crossorigin="anonymous"
        ></script>
    </head>
    <body>
        <div id="main">
            <!-- đèn trạng thái đang tắt  -->
            <div class="content-led" id="led1">
                <div class="img-led">
                    <div class="img">
                        <img
                            class="led"
                            src="https://res.cloudinary.com/vantiennn/image/upload/v1653213936/led_vujitx.png"
                            alt=""
                        />
                    </div>
                    <h3 class="status-led">OFF</h3>
                    <h3 class="dics">LED 1</h3>
                </div>
                <div class="body-setting">
                    <div class="btn-setting-led">
                        <h3 class="btn-title-setting">Cài đặt hẹn giờ:</h3>
                        <button
                            class="btn"
                            data-bs-target="#led1TimeOnModel"
                            data-bs-toggle="modal"
                        >
                            Hẹn giờ bật
                        </button>
                        <button
                            class="btn"
                            data-bs-target="#led1TimeOffModel"
                            data-bs-toggle="modal"
                        >
                            Hẹn giờ tắt
                        </button>
                    </div>

                    <div class="body-setting-timer" id="led1Counter"></div>
                </div>
            </div>

            <!-- đèn trạng thái đang tắt  -->
            <div class="content-led" id="led2">
                <div class="img-led">
                    <div class="img">
                        <img
                            class="led"
                            src="https://res.cloudinary.com/vantiennn/image/upload/v1653213936/led_vujitx.png"
                            alt=""
                        />
                    </div>
                    <h3 class="status-led">OFF</h3>
                    <h3 class="dics">LED 2</h3>
                </div>
                <div class="body-setting">
                    <div class="btn-setting-led">
                        <h3 class="btn-title-setting">Cài đặt hẹn giờ:</h3>
                        <button
                            class="btn"
                            data-bs-target="#led2TimeOnModel"
                            data-bs-toggle="modal"
                        >
                            Hẹn giờ bật
                        </button>
                        <button
                            class="btn"
                            data-bs-target="#led2TimeOffModel"
                            data-bs-toggle="modal"
                        >
                            Hẹn giờ tắt
                        </button>
                    </div>

                    <div class="body-setting-timer" id="led2Counter"></div>
                </div>
            </div>
        </div>

        <!-- Modal Off 1-->
        <div
            class="modal fade"
            id="led1TimeOffModel"
            data-bs-backdrop="static"
            data-bs-keyboard="false"
            tabindex="-1"
            aria-labelledby="led1TimeOffModelLabel"
            aria-hidden="true"
        >
            <div class="modal-dialog">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title">Hẹn giờ tắt đèn 1</h5>
                        <button
                            type="button"
                            class="btn-close"
                            data-bs-dismiss="modal"
                            aria-label="Close"
                        ></button>
                    </div>
                    <div class="modal-body">
                        <label>Nhập thời gian tắt: </label>
                        <input
                            type="datetime-local"
                            class="ledDateOff"
                            id="led1DateOff"
                        />
                    </div>
                    <div class="modal-footer">
                        <button
                            type="button"
                            class="btn btn-secondary ledBtnCloseOff"
                            data-bs-dismiss="modal"
                            id="led1BtnCloseOff"
                        >
                            Close
                        </button>
                        <button
                            type="button"
                            id="led1BtnSubmitOff"
                            class="btn btn-primary ledBtnSubmitOff"
                        >
                            Save changes
                        </button>
                    </div>
                </div>
            </div>
        </div>

        <!-- Modal On 1-->
        <div
            class="modal fade"
            id="led1TimeOnModel"
            data-bs-backdrop="static"
            data-bs-keyboard="false"
            tabindex="-1"
            aria-labelledby="led1TimeOnModelLabel"
            aria-hidden="true"
        >
            <div class="modal-dialog">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title">Hẹn giờ bật đèn 1</h5>
                        <button
                            type="button"
                            class="btn-close"
                            data-bs-dismiss="modal"
                            aria-label="Close"
                        ></button>
                    </div>
                    <div class="modal-body">
                        <label>Nhập thời gian tắt: </label>
                        <input
                            type="datetime-local"
                            id="led1DateOn"
                            class="ledDateOn"
                        />
                    </div>
                    <div class="modal-footer">
                        <button
                            type="button"
                            class="btn btn-secondary ledBtnCloseOn"
                            data-bs-dismiss="modal"
                            id="led1BtnCloseOn"
                        >
                            Close
                        </button>
                        <button
                            type="button"
                            id="led1BtnSubmitOn"
                            class="btn btn-primary ledBtnSubmitOn"
                        >
                            Save changes
                        </button>
                    </div>
                </div>
            </div>
        </div>

        <!-- Modal Off 2-->
        <div
            class="modal fade"
            id="led2TimeOffModel"
            data-bs-backdrop="static"
            data-bs-keyboard="false"
            tabindex="-2"
            aria-labelledby="led2TimeOffModelLabel"
            aria-hidden="true"
        >
            <div class="modal-dialog">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title">Hẹn giờ tắt đèn 2</h5>
                        <button
                            type="button"
                            class="btn-close"
                            data-bs-dismiss="modal"
                            aria-label="Close"
                        ></button>
                    </div>
                    <div class="modal-body">
                        <label>Nhập thời gian tắt: </label>
                        <input
                            type="datetime-local"
                            class="ledDateOff"
                            id="led2DateOff"
                        />
                    </div>
                    <div class="modal-footer">
                        <button
                            type="button"
                            class="btn btn-secondary ledBtnCloseOff"
                            data-bs-dismiss="modal"
                            id="led2BtnCloseOff"
                        >
                            Close
                        </button>
                        <button
                            type="button"
                            id="led2BtnSubmitOff"
                            class="btn btn-primary ledBtnSubmitOff"
                        >
                            Save changes
                        </button>
                    </div>
                </div>
            </div>
        </div>

        <!-- Modal On 2-->
        <div
            class="modal fade"
            id="led2TimeOnModel"
            data-bs-backdrop="static"
            data-bs-keyboard="false"
            tabindex="-2"
            aria-labelledby="led2TimeOnModelLabel"
            aria-hidden="true"
        >
            <div class="modal-dialog">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title">Hẹn giờ bật đèn 2</h5>
                        <button
                            type="button"
                            class="btn-close"
                            data-bs-dismiss="modal"
                            aria-label="Close"
                        ></button>
                    </div>
                    <div class="modal-body">
                        <label>Nhập thời gian tắt: </label>
                        <input
                            type="datetime-local"
                            id="led2DateOn"
                            class="ledDateOn"
                        />
                    </div>
                    <div class="modal-footer">
                        <button
                            type="button"
                            class="btn btn-secondary ledBtnCloseOn"
                            data-bs-dismiss="modal"
                            id="led2BtnCloseOn"
                        >
                            Close
                        </button>
                        <button
                            type="button"
                            id="led2BtnSubmitOn"
                            class="btn btn-primary ledBtnSubmitOn"
                        >
                            Save changes
                        </button>
                    </div>
                </div>
            </div>
        </div>
    </body>
    <script>

        
        

    
        window.addEventListener("DOMContentLoaded", () => {
          var gateway = `ws://${window.location.hostname}/ws`;
          var websocket;
          window.addEventListener('load', onLoad);
          function initWebSocket() {
            console.log('Trying to open a WebSocket connection...');
            websocket = new WebSocket(gateway);
            websocket.onopen    = onOpen;
            websocket.onclose   = onClose;
            websocket.onmessage = onMessage; // <-- add this line
          }
          function onOpen(event) {
            console.log('Connection opened');
          }
          function onClose(event) {
            console.log('Connection closed');
            setTimeout(initWebSocket, 2000);
          }
          function onMessage(event) {
            if (event.data == "/26/on"){ 
              handleTurnOnLed("#led1", 26);
            }
            if (event.data == "/26/off"){ 
              handleTurnOffLed("#led1", 26);
            }
            if (event.data == "/27/on"){ 
              handleTurnOnLed("#led2", 27);
            }
            if (event.data == "/27/off"){ 
              handleTurnOffLed("#led2", 27);
            }
            console.log("on Message", event);
            
          }
          function onLoad(event) {
            initWebSocket();
          }
            const led1Port = 26;
            const led2Port = 27;
            function ajaxTurnOn(port) {
                $.ajax({
                    url: `/${port}/on`,
                    method: "GET",
                });
            }
            function ajaxTurnOff(port) {
                $.ajax({
                    url: `/${port}/off`,
                    method: "GET",
                });
            }

            function convertTimestampToCustom(time) {
                const result = {
                    days: 0,
                    hours: 0,
                    minutes: 0,
                    seconds: 0,
                };
                result.days = Math.floor(time / (1000 * 60 * 60 * 24));
                result.hours = Math.floor(time / (1000 * 60 * 60) %% 24);
                result.minutes = Math.floor((time / (1000 * 60)) %% 60);
                result.seconds = Math.floor((time / 1000) %% 60);
                var string = "";
                if (result.days > 0) string += result.days + "d ";
                if (result.hours > 0) string += result.hours + "h ";
                if (result.minutes > 0) string += result.minutes + "m ";
                if (result.seconds >= 0) string += result.seconds + "s ";

                return string;
            }
            function itemCounter(id, type, timestamp, timeOut, timeInterval) {
                console.log(timeOut, timeInterval);
                return `
                    <div class="content-setting" id="${id}" data-id="${id}" data-timeout="${timeOut}" data-timeinterval="${timeInterval}">
                        <h3 class="title-setting">${type}:</h3>
                        <p class="countdown timmer">${convertTimestampToCustom(
                            timestamp
                        )}</p>
                        <span class="cancel-timmer" style="    display: block;
                        margin: auto 0;
                        margin-left: auto;
                        margin-right: 8px;
                        cursor: pointer;">X</span>
                    </div>`;
            }

            function handleCancelTimmer(
                counterContainer,
                timeout,
                timeInterval
            ) {
                const couterContainerEle =
                    document.querySelector(counterContainer);

                couterContainerEle.querySelector(".cancel-timmer").onclick =
                    function () {
                        this.parentElement.remove();
                        clearTimeout(timeout);
                        clearInterval(timeInterval);
                    };
            }

            function handleCancelAllTimmer() {
                const counterContainerEle =
                    document.querySelectorAll(".cancel-timmer");
                for (let i = 0; i < counterContainerEle.length; i++) {
                    const counterItemEle = counterContainerEle[i];
                    counterItemEle.onclick = function () {
                        const parentEle = this.parentElement;
                        const timeOut = parentEle.getAttribute("data-timeout");
                        const timeInterval =
                            parentEle.getAttribute("data-timeinterval");
                        clearTimeout(timeOut);
                        clearInterval(timeInterval);
                        parentEle.remove();
                    };
                }
            }

            function handleToggleLed(parent, port) {
                const toggleEle = document.querySelector(parent);
                const imageEle = toggleEle.querySelector(".img");
                const statusEle = toggleEle.querySelector(".status-led");
                console.log({ toggle1Ele, imageEle, statusEle });
//              imageEle.classList.toggle("on");
//              console.log(statusEle.textContent);
                if (statusEle.textContent === "ON") {
//                    statusEle.textContent = "OFF";
                    //ajaxTurnOff(port);
                    websocket.send(`/${port}/off`);
                } else {
//                    statusEle.textContent = "ON";
                    //ajaxTurnOn(port);
                    console.log(`/${port}/on`);
                    websocket.send(`/${port}/on`);
                }
            }

            function handleTurnOffLed(parent, port) {
                const toggleEle = document.querySelector(parent);
                const imageEle = toggleEle.querySelector(".img");
                const statusEle = toggleEle.querySelector(".status-led");
                console.log({ toggle1Ele, imageEle, statusEle });
                imageEle.classList.remove("on");
                statusEle.textContent = "OFF";
               
            }
            function handleTurnOnLed(parent, port) {
                console.log(parent)
                const toggleEle = document.querySelector(parent);
                const imageEle = toggleEle.querySelector(".img");
                const statusEle = toggleEle.querySelector(".status-led");
                console.log({ toggle1Ele, imageEle, statusEle });
                imageEle.classList.add("on");
                statusEle.textContent = "ON";
                //ajaxTurnOn(port);
            }

            function handleModelOffClick(
                parent,
                modelParent,
                counterParent,
                port
            ) {
                const modelOff = document.querySelector(modelParent);
                const dateOff = modelOff.querySelector(".ledDateOff");
                const btnCloseOff = modelOff.querySelector(".ledBtnCloseOff");
                const counter = document.querySelector(counterParent);
                console.log({ modelOff, dateOff, btnCloseOff, counter });
                const now = new Date();
                if (!dateOff.value) {
                    alert("Bạn chưa chọn thời gian hẹn giờ.");
                    return;
                }

                const timer = new Date(dateOff.value);
                const timestamp = timer - now;
                const expireTime = new Date(dateOff.value);
                if (timestamp <= 0) {
                    alert("Bạn cần đặt thời gian lớn hơn hiện tại");
                    return;
                }

                var tempTime = setTimeout(function () {
                    btnCloseOff.click();
                    var timeout = setTimeout(function (e) {
                        //handleTurnOffLed(parent, port);
                        websocket.send(`/${port}/off`);
                        document.querySelector("#timer-" + timeout).remove();
                        clearInterval(timeInterval);
                    }, timestamp);

                    const timeInterval = setInterval(function () {
                        var currentDate = new Date();
                        newTimeStamp = expireTime - currentDate;
                        const timerContainerEle = document.querySelector(
                            "#timer-" + timeout
                        );
                        timerContainerEle.querySelector(".timmer").textContent =
                            convertTimestampToCustom(newTimeStamp);
                    }, 1000);
                    var newTimeStamp = timestamp;
                    counter.innerHTML =
                        counter.innerHTML +
                        itemCounter(
                            "timer-" + timeout,
                            "Tắt sau",
                            newTimeStamp,
                            timeout,
                            timeInterval
                        );
                    handleCancelAllTimmer();
                }, timestamp %% 1000);
            }
            function handleModelOnClick(
                parent,
                modelParent,
                counterParent,
                port
            ) {
                const modelOn = document.querySelector(modelParent);
                const dateOn = modelOn.querySelector(".ledDateOn");
                const btnCloseOn = modelOn.querySelector(".ledBtnCloseOn");
                const counter = document.querySelector(counterParent);
                console.log({ modelOn, dateOn, btnCloseOn, counter });
                const now = new Date();
                if (!dateOn.value) {
                    alert("Bạn chưa chọn thời gian hẹn giờ.");
                    return;
                }

                const timer = new Date(dateOn.value);
                const timestamp = timer - now;
                const expireTime = new Date(dateOn.value);
                if (timestamp <= 0) {
                    alert("Bạn cần đặt thời gian lớn hơn hiện tại");
                    return;
                }

                var tempTime = setTimeout(function () {
                    btnCloseOn.click();
                    var timeout = setTimeout(function (e) {
                        //handleTurnOnLed(parent, port);
                        websocket.send(`/${port}/on`);
                        document.querySelector("#timer-" + timeout).remove();
                        clearInterval(timeInterval);
                    }, timestamp);

                    var newTimeStamp;

                    const timeInterval = setInterval(function () {
                        var currentDate = new Date();
                        newTimeStamp = expireTime - currentDate;
                        const timerContainerEle = document.querySelector(
                            "#timer-" + timeout
                        );
                        timerContainerEle.querySelector(".timmer").textContent =
                            convertTimestampToCustom(newTimeStamp);
                    }, 1000);
                    counter.innerHTML =
                        counter.innerHTML +
                        itemCounter(
                            "timer-" + timeout,
                            "Bật sau",
                            newTimeStamp,
                            timeout,
                            timeInterval
                        );
                    handleCancelAllTimmer();
                }, timestamp %% 1000);
            }
            const light1Ele = document.querySelector("#led1");
            const toggle1Ele = light1Ele.querySelector(".img-led");
            const btnSubmit1Off = document.querySelector("#led1BtnSubmitOff");
            const btnSubmit1On = document.querySelector("#led1BtnSubmitOn");
            toggle1Ele.onclick = function () {
                console.log("fuck");
                handleToggleLed("#led1", led1Port);
            };
            btnSubmit1Off.onclick = function () {
                handleModelOffClick(
                    "#led1",
                    "#led1TimeOffModel",
                    "#led1Counter",
                    led1Port
                );
            };
            btnSubmit1On.onclick = function () {
                handleModelOnClick(
                    "#led1",
                    "#led1TimeOnModel",
                    "#led1Counter",
                    led1Port
                );
            };

            const light2Ele = document.querySelector("#led2");
            const toggle2Ele = light2Ele.querySelector(".img-led");
            const btnSubmit2Off = document.querySelector("#led2BtnSubmitOff");
            const btnSubmit2On = document.querySelector("#led2BtnSubmitOn");
            toggle2Ele.onclick = function () {
                handleToggleLed("#led2", led2Port);
            };
            btnSubmit2Off.onclick = function () {
                handleModelOffClick(
                    "#led2",
                    "#led2TimeOffModel",
                    "#led2Counter",
                    led2Port
                );
            };
            btnSubmit2On.onclick = function () {
                handleModelOnClick(
                    "#led2",
                    "#led2TimeOnModel",
                    "#led2Counter",
                    led2Port
                );
            };
        });
    </script>
    <style>
        * {
            padding: 0;
            margin: 0;
            box-sizing: border-box;
        }

        html {
            font-family: cursive !important;
        }

        body {
            height: 100vh;
            display: flex;
            align-items: center;
            justify-content: center;
            background-color: #37343a !important;
        }

        .main {
        }

        .content-led {
            /* height: 200px; */
            background-color: rgb(74, 83, 78);
            display: flex;
            width: 500px;
            margin: 10px 0;
            border-radius: 15px;
            overflow: hidden;
            flex-wrap: wrap;
        }

        .img-led {
            cursor: pointer;
            background-color: #444345;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 250px;
            min-width: 250px;
            position: relative;
            overflow: hidden;
        }

        .on {
            filter: drop-shadow(0 0 85px #ffef30) drop-shadow(0 0 25px #ffef30)
                drop-shadow(600px 600px 600px #ffef30)
                drop-shadow(0 0 85px #ffef30);
        }

        .led {
            width: 200px;
        }

        .status-led {
            position: absolute;
            top: 7px;
            right: 10px;
        }

        .btn {
            margin-top: 25px;
            margin-left: 5px;
            font-size: 18px;
            background-color: #37343a !important;
            border: none;
            color: #cbcbcf !important;
            padding: 10px;
            border-radius: 10px;
            cursor: pointer;
        }

        .btn:hover {
            background-color: #ccc;
            color: #37343a;
        }

        .dics {
            position: absolute;
            bottom: 6px;
            left: 10px;
        }

        .body-setting {
            display: flex;
            flex-direction: column;
            border-radius: 50px;
        }

        .body-setting-timer {
            width: 100%%;
            height: 100px;
            background-color: #ccc;
            margin-left: 7px;
            margin-top: 35px;
            border: 3px solid #000;
            border-radius: 5px;
            overflow: auto;
        }

        .btn-title-setting {
            margin-left: 10px;
            font-size: 25px;
        }

        .content-setting {
            display: flex;
            /* line-height: 30px; */
            height: 30px;
            width: 100%%;
        }

        .title-setting {
            line-height: 30px;
            font-size: 16px;
            margin-left: 5px;
        }

        .countdown {
            line-height: 30px;
        }

        @media (max-width: 46.1875em) {
            .content-led {
                display: block;
                height: 350px;
                width: 300px;
            }

            .img-led {
                height: 150px;
                min-width: 150px;
            }

            .on {
                filter: drop-shadow(0 0 10px #ffef30)
                    drop-shadow(0 0 14px #ffef30)
                    drop-shadow(75px 75px 75px #ffef30)
                    drop-shadow(0 0 25px #ffef30);
            }

            .btn-title-setting {
                text-align: center;
            }

            .btn {
                margin-top: 10px;
            }

            .led {
                width: 150px;
            }

            .body-setting-timer {
                width: 280px;
                height: 100px;
                margin: 8px auto;
            }

            .btn-setting-led {
                text-align: center;
            }

            .title-setting {
                margin-left: 30px;
            }
        }
    </style>
</html>



)rawliteral";
