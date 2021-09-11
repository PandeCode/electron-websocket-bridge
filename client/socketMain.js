let $ = document.querySelector.bind(document);

const nextBtn = $("#nextBtn");
const playBtn = $("#playBtn");
const pauseBtn = $("#pauseBtn");
const previousBtn = $("#previousBtn");
const playPauseBtn = $("#playPauseBtn");
const playStateBtn = $("#playStateBtn");
const likeCurrentBtn = $("#likeCurrentBtn");
const enableRepeatBtn = $("#enableRepeatBtn");
const repeatStatusBtn = $("#repeatStatusBtn");
const toggleShuffleBtn = $("#toggleShuffleBtn");
const dislikeCurrentBtn = $("#dislikeCurrentBtn");
const isCurrentLikedBtn = $("#isCurrentLikedBtn");
const enableRepeatOneBtn = $("#enableRepeatOneBtn");
const disableRepeatOneBtn = $("#disableRepeatOneBtn");
const toggleLikeCurrentBtn = $("#toggleLikeCurrentBtn");

nextBtn.disabled =
	playBtn.disabled =
	pauseBtn.disabled =
	previousBtn.disabled =
	playPauseBtn.disabled =
	playStateBtn.disabled =
	likeCurrentBtn.disabled =
	enableRepeatBtn.disabled =
	repeatStatusBtn.disabled =
	toggleShuffleBtn.disabled =
	dislikeCurrentBtn.disabled =
	isCurrentLikedBtn.disabled =
	enableRepeatOneBtn.disabled =
	disableRepeatOneBtn.disabled =
	toggleLikeCurrentBtn.disabled =
		true;

document
	.getElementById("activateWebSocketBtn")
	.addEventListener("click", () => {
		activeWebSockets();
		nextBtn.disabled =
			playBtn.disabled =
			pauseBtn.disabled =
			previousBtn.disabled =
			playPauseBtn.disabled =
			playStateBtn.disabled =
			likeCurrentBtn.disabled =
			enableRepeatBtn.disabled =
			repeatStatusBtn.disabled =
			toggleShuffleBtn.disabled =
			dislikeCurrentBtn.disabled =
			isCurrentLikedBtn.disabled =
			enableRepeatOneBtn.disabled =
			disableRepeatOneBtn.disabled =
			toggleLikeCurrentBtn.disabled =
				false;
		$("#activateWebSocketBtn").disabled = true;
	});

function activeWebSockets() {
	const ws = new WebSocket("ws://localhost:8080/client/ws");

	ws.addEventListener("open", (event) => {
		console.info("Hello Server!", event);
		ws.send("Hello Server!");
	});
	ws.addEventListener("close", (event) => {
		console.warn("Bye Server!", event);
	});
	ws.addEventListener("error", (event) => {
		console.error("Error with server", event);
	});
	ws.addEventListener("message", (event) => {
		console.info("Message from server ", event.data);
	});

	nextBtn.addEventListener("click", () => {
		ws.send("next");
	});
	playBtn.addEventListener("click", () => {
		ws.send("play");
	});
	pauseBtn.addEventListener("click", () => {
		ws.send("pause");
	});
	previousBtn.addEventListener("click", () => {
		ws.send("previous");
	});
	playPauseBtn.addEventListener("click", () => {
		ws.send("playPause");
	});
	playStateBtn.addEventListener("click", () => {
		ws.send("playState");
	});
	likeCurrentBtn.addEventListener("click", () => {
		ws.send("likeCurrent");
	});
	enableRepeatBtn.addEventListener("click", () => {
		ws.send("enableRepeat");
	});
	repeatStatusBtn.addEventListener("click", () => {
		ws.send("repeatStatus");
	});
	toggleShuffleBtn.addEventListener("click", () => {
		ws.send("toggleShuffle");
	});
	dislikeCurrentBtn.addEventListener("click", () => {
		ws.send("dislikeCurrent");
	});
	isCurrentLikedBtn.addEventListener("click", () => {
		ws.send("isCurrentLiked");
	});
	enableRepeatOneBtn.addEventListener("click", () => {
		ws.send("enableRepeatOne");
	});
	disableRepeatOneBtn.addEventListener("click", () => {
		ws.send("disableRepeatOne");
	});
	toggleLikeCurrentBtn.addEventListener("click", () => {
		ws.send("toggleLikeCurrent");
	});
}

const BASE_URL = "http://localhost:8080/command/";

$("#nextRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "next").then(d => console.log(d));
});
$("#playRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "play").then(d => console.log(d));
});
$("#pauseRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "pause").then(d => console.log(d));
});
$("#previousRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "previous").then(d => console.log(d));
});
$("#playPauseRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "playPause").then(d => console.log(d));
});
$("#playStateRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "playState").then(d => console.log(d));
});
$("#likeCurrentRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "likeCurrent").then(d => console.log(d));
});
$("#enableRepeatRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "enableRepeat").then(d => console.log(d));
});
$("#repeatStatusRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "repeatStatus").then(d => console.log(d));
});
$("#toggleShuffleRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "toggleShuffle").then(d => console.log(d));
});
$("#dislikeCurrentRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "dislikeCurrent").then(d => console.log(d));
});
$("#isCurrentLikedRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "isCurrentLiked").then(d => console.log(d));
});
$("#enableRepeatOneRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "enableRepeatOne").then(d => console.log(d));
});
$("#disableRepeatOneRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "disableRepeatOne").then(d => console.log(d));
});
$("#toggleLikeCurrentRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "toggleLikeCurrent").then(d => console.log(d));
});
