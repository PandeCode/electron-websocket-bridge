$ = document.querySelector.bind(document);

const nextBtn = $("#nextBtn");
const playBtn = $("#playBtn");
const pauseBtn = $("#pauseBtn");
const previousBtn = $("#previousBtn");
const playPauseBtn = $("#playPauseBtn");
const likeCurrentBtn = $("#likeCurrentBtn");
const enableRepeatBtn = $("#enableRepeatBtn");
const getRepeatStatusBtn = $("#getRepeatStatusBtn");
const toggleShuffleBtn = $("#toggleShuffleBtn");
const dislikeCurrentBtn = $("#dislikeCurrentBtn");
const isCurrentLikedBtn = $("#isCurrentLikedBtn");
const enableRepeatOneBtn = $("#enableRepeatOneBtn");
const toggleLikeCurrentBtn = $("#toggleLikeCurrentBtn");

document
	.getElementById("activateWebSocketBtn")
	.addEventListener("click", () => {
		activeWebSockets();
		nextBtn.disabled =
			playBtn.disabled =
			pauseBtn.disabled =
			previousBtn.disabled =
			playPauseBtn.disabled =
			likeCurrentBtn.disabled =
			enableRepeatBtn.disabled =
			getRepeatStatusBtn.disabled =
			toggleShuffleBtn.disabled =
			dislikeCurrentBtn.disabled =
			isCurrentLikedBtn.disabled =
			enableRepeatOneBtn.disabled =
			toggleLikeCurrentBtn.disabled =
				false;
		$("#activateWebSocketBtn").disabled = true;
	});

function activeWebSockets() {
	const ws = new WebSocket("ws://localhost:8080/client/ws");

	ws.addEventListener("open", (event) => {
		console.info("Hello Server!", event);
		ws.send('{"type": "command", "message": "Hello Server!"}');
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
		ws.send('{"type": "command", "message": "next"}');
	});
	playBtn.addEventListener("click", () => {
		ws.send('{"type": "command", "message": "play"}');
	});
	pauseBtn.addEventListener("click", () => {
		ws.send('{"type": "command", "message": "pause"}');
	});
	previousBtn.addEventListener("click", () => {
		ws.send('{"type": "command", "message": "previous"}');
	});
	playPauseBtn.addEventListener("click", () => {
		ws.send('{"type": "command", "message": "playPause"}');
	});
	likeCurrentBtn.addEventListener("click", () => {
		ws.send('{"type": "command", "message": "likeCurrent"}');
	});
	enableRepeatBtn.addEventListener("click", () => {
		ws.send('{"type": "command", "message": "enableRepeat"}');
	});
	getRepeatStatusBtn.addEventListener("click", () => {
		ws.send('{"type": "command", "message": "getRepeatStatus"}');
	});
	toggleShuffleBtn.addEventListener("click", () => {
		ws.send('{"type": "command", "message": "toggleShuffle"}');
	});
	dislikeCurrentBtn.addEventListener("click", () => {
		ws.send('{"type": "command", "message": "dislikeCurrent"}');
	});
	isCurrentLikedBtn.addEventListener("click", () => {
		ws.send('{"type": "command", "message": "isCurrentLiked"}');
	});
	enableRepeatOneBtn.addEventListener("click", () => {
		ws.send('{"type": "command", "message": "enableRepeatOne"}');
	});
	toggleLikeCurrentBtn.addEventListener("click", () => {
		ws.send('{"type": "command", "message": "toggleLikeCurrent"}');
	});
}
