const Hackify = {
	_likeBtn:
		"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > button",
	_currentSongAlbumArt:
		"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div > div > div > a > div > div > div > img",
	_currentSong:
		"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div > div.standalone-ellipsis-one-line > span > a",
	_currentSongArtist:
		"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div > div.standalone-ellipsis-one-line > span > span > a",
	_nextBtn:
		"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > div.player-controls__right > button",
	_previousBtn:
		"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > div.player-controls__left > button:nth-child(2)",
	_playPauseBtn:
		"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > button",
	_shuffleBtn:
		"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > div.player-controls__left > button",
	_repeatBtn:
		"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > div.player-controls__right > button:nth-child(2)",

	_click: (selector: string): void =>
		document.querySelector<HTMLElement>(selector).click(),
	_getArialLabel: (selector: string): string =>
		document.querySelector<HTMLElement>(selector).ariaLabel,
	_getInnerText: (selector: string): string =>
		document.querySelector<HTMLElement>(selector).innerText,
	_getElement: (selector: string): HTMLElement =>
		document.querySelector<HTMLElement>(selector),

	getInfo: () => ({
		currentSong: Hackify.getCurrentSong(),
		currentSongArtist: Hackify.getCurrentSongArtist(),
		currentSongAlbumArt: Hackify.getCurrentSongAlbumArt(),
		isCurrentLiked: Hackify.getIsCurrentLiked(),
		repeatStatus: Hackify.getRepeatStatus(),
		shuffleStatus: Hackify.getIsShuffleOn(),
	}),

	getCurrentSongArtist: () =>
		Hackify._getInnerText(Hackify._currentSongArtist),
	getCurrentSong: () => Hackify._getInnerText(Hackify._currentSong),
	getCurrentSongAlbumArt: () =>
		document.querySelector<HTMLImageElement>(Hackify._currentSongAlbumArt)
			.src,

	next: () => Hackify._click(Hackify._nextBtn),
	previous: () => Hackify._click(Hackify._previousBtn),

	getIsShuffleOn: () =>
		Hackify._getArialLabel(Hackify._shuffleBtn) === "Disable shuffle",
	toggleShuffle: () => Hackify._click(Hackify._shuffleBtn),
	shuffleOn: () =>
		Hackify.getIsShuffleOn() || Hackify._click(Hackify._shuffleBtn),
	shuffleOff: () =>
		Hackify.getIsShuffleOn() && Hackify._click(Hackify._shuffleBtn),

	getIsPlaying: () =>
		Hackify._getArialLabel(Hackify._playPauseBtn) === "Pause",
	playPause: () => Hackify._click(Hackify._playPauseBtn),
	play: () => Hackify.getIsPlaying() || Hackify.playPause(),
	pause: () => Hackify.getIsPlaying() && Hackify.playPause(),

	getRepeatStatus: (): "Disabled" | "Repeat" | "Repeat One" | "Unknown" => {
		switch (Hackify._getArialLabel(Hackify._repeatBtn)) {
			case "Enable repeat":
				return "Disabled";
			case "Enable repeat one":
				return "Repeat";
			case "Disable repeat":
				return "Repeat One";
			default:
				console.error("Other Repeat Label, Very Bad");
				return "Unknown";
		}
	},

	disableRepeat: () => {
		const re = Hackify._getElement(Hackify._repeatBtn);
		if (Hackify.getRepeatStatus() === "Repeat") {
			re.click();
			re.click();
		} else if (Hackify.getRepeatStatus() === "Repeat One") {
			re.click();
		}
	},

	enableRepeatOne: () => {
		const repeatElement = document.querySelector<HTMLButtonElement>(
			Hackify._repeatBtn,
		);
		if (Hackify.getRepeatStatus() === "Disabled") {
			repeatElement.click();
			repeatElement.click();
		} else if (Hackify.getRepeatStatus() === "Repeat") {
			repeatElement.click();
		}
	},

	enableRepeat: () => {
		const repeatElement = document.querySelector<HTMLButtonElement>(
			Hackify._repeatBtn,
		);
		if (Hackify.getRepeatStatus() === "Repeat") {
			repeatElement.click();
			repeatElement.click();
		} else if (Hackify.getRepeatStatus() === "Repeat One") {
			repeatElement.click();
		}
	},

	getIsCurrentLiked: () =>
		Hackify._getElement(Hackify._likeBtn).ariaChecked === "true",
	toggleLike: () => Hackify._click(Hackify._likeBtn),
	likeCurrent: () => Hackify.getIsCurrentLiked() || Hackify.toggleLike(),
	dislikeCurrent: () => Hackify.getIsCurrentLiked() && Hackify.toggleLike(),

	/** @type {WebSocket} */ ws: null,

	/** @type {number} */ interval: null,

	/** @type {number} */ startListeningCalls: 0,

	wsTrySend: (type: string, message: any) => {
		if (Hackify.ws != null)
			if (Hackify.ws.readyState == WebSocket.OPEN)
				Hackify.ws.send(JSON.stringify({ type, message }));
			else console.error("Hey the socket is closed");
		else console.error("Hey the socket is not defined");
	},

	startListening: () => {
		console.info("Start Listening Call: ", ++Hackify.startListeningCalls);
		let socketOpen = false;

		if (Hackify.ws != null) {
			if (Hackify.ws.readyState === WebSocket.OPEN) return true;
			else {
				delete Hackify.ws;
				Hackify.ws = null;
			}
		}

		try {
			Hackify.ws = new WebSocket("ws://localhost:8080/ws");
		} catch (e) {
			return false;
		}

		if (Hackify.ws != null)
			if (Hackify.ws.readyState === WebSocket.OPEN)
				clearInterval(Hackify.interval);

		Hackify.ws.addEventListener("open", (event: Event) => {
			if (Hackify.interval != null) {
				clearInterval(Hackify.interval);
				Hackify.interval = null;
			}
			socketOpen = true;
			console.info("Hello Server!", event);
			Hackify.ws.send(`{"type": "info", "message": "hello server!"}`);
		});

		Hackify.ws.addEventListener("close", (event: CloseEvent) => {
			socketOpen = false;
			console.warn("Bye Server!", event);
			if (Hackify.interval === null)
				Hackify.interval = setInterval(() => {
					Hackify.startListening();
					if (Hackify.ws != null)
						if (Hackify.ws.readyState === WebSocket.OPEN)
							clearInterval(Hackify.interval);
				}, 2500);
		});

		Hackify.ws.addEventListener("error", (event: ErrorEvent) => {
			console.error("Error with server", event);
			if (socketOpen)
				Hackify.ws.send(
					`{"type": "error", "message": "problem with WebSocket client"}`,
				);
			else console.error("Hey the socket is closed");
		});

		Hackify.ws.addEventListener("message", (event: MessageEvent) => {
			console.info("Message from server ", event.data);
			let parsedData: { type: string; message: string };
			try {
				parsedData = JSON.parse(event.data);
				if (!parsedData.type)
					throw SyntaxError(
						`No or blank tyoe in format '{"type": "info|error|command|code", "message": ""}'`,
					);
				if (!parsedData.message)
					throw SyntaxError(
						`No or blank message in format '{"type": "info|error|command|code", "message": ""}'`,
					);
			} catch (err: SyntaxError | any) {
				Hackify.ws.send(
					`{"type": "error", "message": "${err.toString()}"}`,
				);
				console.error(`Error Parsing '${err.toString()}'`);
				return;
			}
			if (parsedData.type === "code") {
				Hackify.wsTrySend("code", eval(parsedData.message));
			} else if (parsedData.type === "command") {
				// prettier-ignore
				switch (parsedData.message) {

					case "play"                   : Hackify.play()                                                                  ; break ;
					case "pause"                  : Hackify.pause()                                                                 ; break ;
					case "playPause"              : Hackify.playPause()                                                             ; break ;
					case "next"                   : Hackify.next()                                                                  ; break ;
					case "previous"               : Hackify.previous()                                                              ; break ;

					case "toggleLike"             : Hackify.toggleLike()                                                            ; break ;
					case "likeCurrent"            : Hackify.likeCurrent()                                                           ; break ;
					case "dislikeCurrent"         : Hackify.dislikeCurrent()                                                        ; break ;

					case "enableRepeat"           : Hackify.enableRepeat()                                                          ; break ;
					case "enableRepeatOne"        : Hackify.enableRepeatOne()                                                       ; break ;
					case "disableRepeat"          : Hackify.disableRepeat()                                                         ; break ;

					case "toggleShuffle"          : Hackify.toggleShuffle()                                                         ; break ;

					case "getInfo"                : Hackify.wsTrySend("getInfo"                , JSON.stringify(Hackify.getInfo())) ; break ;
					case "getCurrentSong"         : Hackify.wsTrySend("getCurrentSong"         , Hackify.getCurrentSong())          ; break ;
					case "getCurrentSongAlbumArt" : Hackify.wsTrySend("getCurrentSongAlbumArt" , Hackify.getCurrentSongAlbumArt())  ; break ;
					case "getCurrentSongArtist"   : Hackify.wsTrySend("getCurrentSongArtist"   , Hackify.getCurrentSongArtist())    ; break ;
					case "getIsCurrentLiked"      : Hackify.wsTrySend("getIsCurrentLiked"      , Hackify.getIsCurrentLiked())       ; break ;
					case "getIsPlaying"           : Hackify.wsTrySend("getIsPlaying"           , Hackify.getIsPlaying())            ; break ;
					case "getRepeatStatus"        : Hackify.wsTrySend("getRepeatStatus"        , Hackify.getRepeatStatus())         ; break ;

					default: {
						Hackify.wsTrySend("error", `unknown command${parsedData.message}`);
						console.error("Unknown Command: ", event.data); 
						break;
					}

				}
			}
		});

		return Hackify.ws.readyState === WebSocket.OPEN;
	},
};

console.log("Hackify.startListening();");
