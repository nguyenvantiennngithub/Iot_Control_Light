window.addEventListener("DOMContentLoaded", () => {
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
        result.hours = Math.floor((time / (1000 * 60 * 60)) % 24);
        result.minutes = Math.floor((time / (1000 * 60)) % 60);
        result.seconds = Math.floor((time / 1000) % 60);
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

    function handleCancelTimmer(counterContainer, timeout, timeInterval) {
        const couterContainerEle = document.querySelector(counterContainer);

        couterContainerEle.querySelector(".cancel-timmer").onclick =
            function () {
                this.parentElement.remove();
                clearTimeout(timeout);
                clearInterval(timeInterval);
            };
    }

    function handleCancelAllTimmer() {
        const counterContainerEle = document.querySelectorAll(".cancel-timmer");
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
        imageEle.classList.toggle("on");
        console.log(statusEle.textContent);
        if (statusEle.textContent === "ON") {
            statusEle.textContent = "OFF";
            ajaxTurnOff(port);
        } else {
            statusEle.textContent = "ON";
            ajaxTurnOn(port);
        }
    }

    function handleTurnOffLed(parent, port) {
        const toggleEle = document.querySelector(parent);
        const imageEle = toggleEle.querySelector(".img");
        const statusEle = toggleEle.querySelector(".status-led");
        console.log({ toggle1Ele, imageEle, statusEle });
        imageEle.classList.remove("on");
        statusEle.textContent = "OFF";
        ajaxTurnOff(port);
    }
    function handleTurnOnLed(parent, port) {
        const toggleEle = document.querySelector(parent);
        const imageEle = toggleEle.querySelector(".img");
        const statusEle = toggleEle.querySelector(".status-led");
        console.log({ toggle1Ele, imageEle, statusEle });
        imageEle.classList.add("on");
        statusEle.textContent = "ON";
        ajaxTurnOn(port);
    }

    function handleModelOffClick(parent, modelParent, counterParent, port) {
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
        const expireTime = new Date(dateOff.value);
        const timestamp = timer - now;
        if (timestamp <= 0) {
            alert("Bạn cần đặt thời gian lớn hơn hiện tại");
            return;
        }

        var tempTime = setTimeout(function () {
            btnCloseOff.click();
            var timeout = setTimeout(function (e) {
                handleTurnOffLed(parent, port);
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
        }, timestamp % 1000);
    }
    function handleModelOnClick(parent, modelParent, counterParent, port) {
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
        if (timestamp <= 0) {
            alert("Bạn cần đặt thời gian lớn hơn hiện tại");
            return;
        }

        var tempTime = setTimeout(function () {
            btnCloseOn.click();
            var timeout = setTimeout(function (e) {
                handleTurnOnLed(parent, port);
                document.querySelector("#timer-" + timeout).remove();
                clearInterval(timeInterval);
            }, timestamp);

            var newTimeStamp = timestamp;

            const timeInterval = setInterval(function () {
                newTimeStamp -= 1000;
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
        }, timestamp % 1000);
    }
    const light1Ele = document.querySelector("#led1");
    const toggle1Ele = light1Ele.querySelector(".img-led");
    const btnSubmit1Off = document.querySelector("#led1BtnSubmitOff");
    const btnSubmit1On = document.querySelector("#led1BtnSubmitOn");
    toggle1Ele.onclick = function () {
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
