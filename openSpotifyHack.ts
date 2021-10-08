const SpotifyHackApi = {
	runCode: (code: string) => eval(code),

	next: () =>
		document
			.querySelector<HTMLButtonElement>(
				"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > div.player-controls__right > button",
			)
			.click(),

	previous: () =>
		document
			.querySelector<HTMLButtonElement>(
				"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > div.player-controls__left > button:nth-child(2)",
			)
			.click(),

	isShuffleOn: () =>
		document.querySelector<HTMLButtonElement>(
			"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > div.player-controls__left > button",
		).ariaLabel === "Disable shuffle",

	toggleShuffle: () =>
		document
			.querySelector<HTMLButtonElement>(
				"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > div.player-controls__left > button",
			)
			.click(),

	shuffleOn: () => {
		if (!SpotifyHackApi.isShuffleOn())
			document
				.querySelector<HTMLButtonElement>(
					"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > div.player-controls__left > button",
				)
				.click();
	},

	shuffleOff: () => {
		if (SpotifyHackApi.isShuffleOn())
			document
				.querySelector<HTMLButtonElement>(
					"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > div.player-controls__left > button",
				)
				.click();
	},

	getPlayState: () => {
		if (SpotifyHackApi.isPlaying()) return "Playing";
		else return "Paused";
	},

	isPlaying: () =>
		document.querySelector<HTMLButtonElement>(
			"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > button",
		).ariaLabel === "Pause",

	playPause: () =>
		document
			.querySelector<HTMLButtonElement>(
				"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > button",
			)
			.click(),
	play: () => {
		if (!SpotifyHackApi.isPlaying())
			document
				.querySelector<HTMLButtonElement>(
					"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > button",
				)
				.click();
	},
	pause: () => {
		if (SpotifyHackApi.isPlaying())
			document
				.querySelector<HTMLButtonElement>(
					"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > button",
				)
				.click();
	},

	repeatElementSelector:
		"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > div.player-controls__right > button:nth-child(2)",

	getRepeatStatus: () => {
		switch (
			document.querySelector<HTMLButtonElement>(
				SpotifyHackApi.repeatElementSelector,
			).ariaLabel
		) {
			case "Enable repeat":
				return "Disabled";
			case "Enable repeat one":
				return "Repeat";
			case "Disable repeat":
				return "Repeat One";
			default:
				console.error("Other Repeat Label, Very ");
				return "Unknown";
		}
	},

	disableRepeat: () => {
		const repeatElement = document.querySelector<HTMLButtonElement>(
			SpotifyHackApi.repeatElementSelector,
		);
		if (SpotifyHackApi.getRepeatStatus() === "Repeat") {
			repeatElement.click();
			repeatElement.click();
		} else if (SpotifyHackApi.getRepeatStatus() === "Repeat One") {
			repeatElement.click();
		}
	},

	enableRepeatOne: () => {
		const repeatElement = document.querySelector<HTMLButtonElement>(
			SpotifyHackApi.repeatElementSelector,
		);

		if (SpotifyHackApi.getRepeatStatus() === "Disabled") {
			repeatElement.click();
			repeatElement.click();
		} else if (SpotifyHackApi.getRepeatStatus() === "Repeat") {
			repeatElement.click();
		}
	},

	enableRepeat: () => {
		const repeatElement = document.querySelector<HTMLButtonElement>(
			SpotifyHackApi.repeatElementSelector,
		);

		if (SpotifyHackApi.getRepeatStatus() === "Repeat") {
			repeatElement.click();
			repeatElement.click();
		} else if (SpotifyHackApi.getRepeatStatus() === "Repeat One") {
			repeatElement.click();
		}
	},

	likeElementSelector:
		"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > button",

	getIsCurrentLiked: () =>
		document.querySelector<HTMLButtonElement>(
			SpotifyHackApi.likeElementSelector,
		).ariaChecked === "true",

	toggleLikeCurrent: () =>
		document
			.querySelector<HTMLButtonElement>(
				SpotifyHackApi.likeElementSelector,
			)
			.click(),

	likeCurrent: () =>
		SpotifyHackApi.getIsCurrentLiked() ||
		SpotifyHackApi.toggleLikeCurrent(),
	dislikeCurrent: () =>
		SpotifyHackApi.getIsCurrentLiked() &&
		SpotifyHackApi.toggleLikeCurrent(),

	/** @type {WebSocket} */
	ws: null,
	/** @type {number} */
	interval: null,

	/** @type {number} */
	startListeningCalls: 0,

	startListening: () => {
		console.info(
			"Start Listening Call: ",
			++SpotifyHackApi.startListeningCalls,
		);
		let socketOpen = false;

		if (SpotifyHackApi.ws != null) {
			if (SpotifyHackApi.ws.readyState === WebSocket.OPEN) return true;
			else {
				delete SpotifyHackApi.ws;
				SpotifyHackApi.ws = null;
			}
		}

		try {
			SpotifyHackApi.ws = new WebSocket("ws://localhost:8080/ws");
		} catch (e) {
			return false;
		}

		if (SpotifyHackApi.ws != null)
			if (SpotifyHackApi.ws.readyState === WebSocket.OPEN)
				clearInterval(SpotifyHackApi.interval);

		SpotifyHackApi.ws.addEventListener("open", (event: Event) => {
			if (SpotifyHackApi.interval != null) {
				clearInterval(SpotifyHackApi.interval);
				SpotifyHackApi.interval = null;
			}
			socketOpen = true;
			console.info("Hello Server!", event);
			SpotifyHackApi.ws.send(
				`{"type": "info", "message": "hello server!"}`,
			);
		});

		SpotifyHackApi.ws.addEventListener("close", (event: CloseEvent) => {
			socketOpen = false;
			console.warn("Bye Server!", event);
			if (SpotifyHackApi.interval === null)
				SpotifyHackApi.interval = setInterval(() => {
					SpotifyHackApi.startListening();
					if (SpotifyHackApi.ws != null)
						if (SpotifyHackApi.ws.readyState === WebSocket.OPEN)
							clearInterval(SpotifyHackApi.interval);
				}, 2500);
		});

		SpotifyHackApi.ws.addEventListener("error", (event: ErrorEvent) => {
			console.error("Error with server", event);
			if (socketOpen)
				SpotifyHackApi.ws.send(
					`{"type": "error", "message": "problem with WebSocket client"}`,
				);
			else console.error("Hey the socket is closed");
		});

		SpotifyHackApi.ws.addEventListener("message", (event: MessageEvent) => {
			console.info("Message from server ", event.data);
			let parsedData: { type: string; message: string };
			try {
				parsedData = JSON.parse(event.data);
			} catch (error) {
				if (socketOpen)
					SpotifyHackApi.ws.send(
						`{"type": "error", "message": "failed to parse server's data"}`,
					);
				else console.error("Hey the socket is closed");
				console.error("Failed To parse server's message");
				return;
			}
			if (parsedData.type === "code") {
				if (socketOpen)
					SpotifyHackApi.ws.send(
						`{"type": "code", "message": "${SpotifyHackApi.runCode(
							parsedData.message,
						)}"}`,
					);
				else console.error("Hey the socket is closed");
			} else if (parsedData.type === "command") {
				switch (parsedData.message) {
					case "getIsCurrentLiked": {
						if (socketOpen)
							SpotifyHackApi.ws.send(
								`{"type": "getIsCurrentLiked", "message": "${SpotifyHackApi.getIsCurrentLiked()}"}`,
							);
						else console.error("Hey the socket is closed");
						break;
					}
					case "getRepeatStatus": {
						if (socketOpen)
							SpotifyHackApi.ws.send(
								`{"type": "getRepeatStatus", "message": "${SpotifyHackApi.getRepeatStatus()}"}`,
							);
						else console.error("Hey the socket is closed");
						break;
					}
					case "getPlayState": {
						if (socketOpen)
							SpotifyHackApi.ws.send(
								`{"type": "getPlayState", "message": "${SpotifyHackApi.getPlayState()}"}`,
							);
						else console.error("Hey the socket is closed");
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
							SpotifyHackApi.ws.send(
								`{"type": "error", "message": "unknown command"}`,
							);
						else console.error("Hey the socket is closed");
						console.error("Unknown Command: ", event.data);
						break;
					}
				}
			}
		});

		return SpotifyHackApi.ws.readyState === WebSocket.OPEN;
	},
};
SpotifyHackApi.startListening();
