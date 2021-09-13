//@ts-check
/// <reference path="./globals.d.ts" />
//
const SpotifyHackApi = {
	runCode: (/** @type {string} */ code) => eval(code),
	next: () => Spicetify.Player.next(),
	previous: () => Spicetify.Player.back(),
	toggleShuffle: () => Spicetify.Player.toggleShuffle(),
	shuffleOn: () => Spicetify.Player.setShuffle(true),
	shuffleOff: () => Spicetify.Player.setShuffle(false),
	playPause: () => Spicetify.Player.togglePlay(),
	play: () => Spicetify.Player.play(),
	pause: () => Spicetify.Player.pause(),
	getRepeatStatus: () => Spicetify.Player.getRepeat(),
	disableRepeat: () => Spicetify.Player.setRepeat(0),
	enableRepeatAll: () => Spicetify.Player.setRepeat(1),
	enableRepeat: () => Spicetify.Player.setRepeat(2),

	getIsCurrentLiked: () =>
		document.querySelector(".main-addButton-button")?.ariaChecked ===
		"true",
	toggleLikeCurrent: () =>
		// @ts-ignore
		document.querySelector(".main-addButton-button")?.click(),
	likeCurrent: () =>
		SpotifyHackApi.getIsCurrentLiked() ||
		SpotifyHackApi.toggleLikeCurrent(),
	dislikeCurrent: () =>
		SpotifyHackApi.getIsCurrentLiked() &&
		SpotifyHackApi.toggleLikeCurrent(),

	/** @type {WebSocket} */ ws: null,

	startListening: () => {
		//if (SpotifyHackApi.ws != null)
		//if (SpotifyHackApi.ws.readyState != WebSocket.OPEN) {
		let socketOpen = false;

		SpotifyHackApi.ws = new WebSocket("ws://localhost:8080/ws");
		const ws = SpotifyHackApi.ws;

		ws.addEventListener("open", (event) => {
			socketOpen = true;
			console.info("Hello Server!", event);
			ws.send(`{"type": "info", "message": "hello server!"}`);
		});
		ws.addEventListener("close", (event) => {
			socketOpen = false;
			console.warn("Bye Server!", event);
		});
		ws.addEventListener("error", (event) => {
			console.error("Error with server", event);
			if (socketOpen)
				ws.send(
					`{"type": "error", "message": "problem with WebSocket client"}`,
				);
			else console.error("Hey the socket is closed");
		});
		ws.addEventListener("message", (event) => {
			console.info("Message from server ", event.data);
			let parsedData;
			try {
				parsedData = JSON.parse(event.data);
			} catch (error) {
				if (socketOpen)
					ws.send(
						`{"type": "error", "message": "failed to parse server's data"}`,
					);
				else console.error("Hey the socket is closed");
				console.error("Failed To parse server's message");
				return;
			}
			if (parsedData.type == "code") {
				if (socketOpen)
					ws.send(
						`{"type": "code", "message": "${SpotifyHackApi.runCode(
							parsedData.message,
						)}"}`,
					);
				else console.error("Hey the socket is closed");
			} else if (parsedData.type == "command") {
				switch (parsedData.message) {
					case "getIsCurrentLiked": {
						if (socketOpen)
							ws.send(
								`{"type": "getIsCurrentLiked", "message": "${SpotifyHackApi.getIsCurrentLiked()}"}`,
							);
						else console.error("Hey the socket is closed");
						break;
					}
					case "getRepeatStatus": {
						if (socketOpen)
							ws.send(
								`{"type": "getRepeatStatus", "message": "${SpotifyHackApi.getRepeatStatus()}"}`,
							);
						else console.error("Hey the socket is closed");
						break;
					}
					case "getPlayState": {
						if (socketOpen)
							ws.send(
								`{"type": "getPlayState", "message": "${SpotifyHackApi.getPlayState()}"}`,
							);
						else console.error("Hey the socket is closed");
						break;
					}
					case "disableRepeatOne": {
						SpotifyHackApi.disableRepeatOne();
						break;
					}
					case "dislikeCurrent": {
						SpotifyHackApi.dislikeCurrent();
						break;
					}
					case "enableRepeat": {
						SpotifyHackApi.enableRepeat();
						break;
					}
					case "enableRepeatOne": {
						SpotifyHackApi.enableRepeatOne();
						break;
					}
					case "likeCurrent": {
						SpotifyHackApi.likeCurrent();
						break;
					}
					case "next": {
						SpotifyHackApi.next();
						break;
					}
					case "pause": {
						SpotifyHackApi.pause();
						break;
					}
					case "play": {
						SpotifyHackApi.play();
						break;
					}
					case "playPause": {
						SpotifyHackApi.playPause();
						break;
					}
					case "previous": {
						SpotifyHackApi.previous();
						break;
					}
					case "toggleLikeCurrent": {
						SpotifyHackApi.toggleLikeCurrent();
						break;
					}
					case "toggleShuffle": {
						SpotifyHackApi.toggleShuffle();
						break;
					}
					default: {
						if (socketOpen)
							ws.send(
								`{"type": "error", "message": "unknown command"}`,
							);
						else console.error("Hey the socket is closed");
						console.error("Unknown Command: ", event.data);
						break;
					}
				}
			}
		});
		//}
	},

	render: () => {
		const activeBtn =
			'<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" aria-hidden="true" role="img" width="1.33em" height="1em" preserveAspectRatio="xMidYMid meet" viewBox="0 0 256 193"><path d="M192.44 144.645h31.78V68.339l-35.805-35.804l-22.472 22.472l26.497 26.497v63.14zm31.864 15.931H113.452L86.954 134.08l11.237-11.236l21.885 21.885h45.028l-44.357-44.441l11.32-11.32l44.357 44.358V88.296l-21.801-21.801l11.152-11.153L110.685 0H0l31.696 31.696v.084H97.436l23.227 23.227l-33.96 33.96L63.476 65.74V47.712h-31.78v31.193l55.007 55.007L64.314 156.3l35.805 35.805H256l-31.696-31.529z" fill="#ffffff""/></svg>';
		const inactiveBtn =
			'<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" aria-hidden="true" role="img" width="1.33em" height="1em" preserveAspectRatio="xMidYMid meet" viewBox="0 0 256 193"><path d="M192.44 144.645h31.78V68.339l-35.805-35.804l-22.472 22.472l26.497 26.497v63.14zm31.864 15.931H113.452L86.954 134.08l11.237-11.236l21.885 21.885h45.028l-44.357-44.441l11.32-11.32l44.357 44.358V88.296l-21.801-21.801l11.152-11.153L110.685 0H0l31.696 31.696v.084H97.436l23.227 23.227l-33.96 33.96L63.476 65.74V47.712h-31.78v31.193l55.007 55.007L64.314 156.3l35.805 35.805H256l-31.696-31.529z" fill="#231F20"/></svg>';

		const SpotifyHackBtn = new Spicetify.Topbar.Button(
			"Start Listening",
			inactiveBtn,
			() => {
				SpotifyHackApi.startListening();
				if (SpotifyHackApi.ws != null)
					if (SpotifyHackApi.ws.readyState === WebSocket.OPEN) {
						SpotifyHackBtn.icon = activeBtn;
					}
			},
		);

		setInterval(() => {
			if (SpotifyHackApi.ws != null) {
				if (SpotifyHackApi.ws.readyState == WebSocket.OPEN) {
					SpotifyHackBtn.icon = activeBtn;
				} else {
					SpotifyHackBtn.icon = inactiveBtn;
				}
			}
		}, 1000);
	},
};

(() => {
	SpotifyHackApi.render();
})();
