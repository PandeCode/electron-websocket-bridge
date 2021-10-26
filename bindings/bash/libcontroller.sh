#!/bin/env bash

commands=(
	disableRepeatOne
	dislikeCurrent
	enableRepeat
	enableRepeatOne
	isCurrentLiked
	likeCurrent
	next
	pause
	play
	playPause
	getIsPlaying
	previous
	repeatStatus
	toggleLikeCurrent
	toggleShuffle
)

curlPlayer() {
	curl http://localhost:8080/command/$1
}

runCommand() {
	case $1 in
		"disableRepeatOne") curlPlayer disableRepeatOne ;;
		"dislikeCurrent") curlPlayer dislikeCurrent ;;
		"enableRepeat") curlPlayer enableRepeat ;;
		"enableRepeatOne") curlPlayer enableRepeatOne ;;
		"isCurrentLiked") curlPlayer isCurrentLiked ;;
		"likeCurrent") curlPlayer likeCurrent ;;
		"next") curlPlayer next ;;
		"pause") curlPlayer pause ;;
		"play") curlPlayer play ;;
		"playPause") curlPlayer playPause ;;
		"getIsPlaying") curlPlayer getIsPlaying ;;
		"previous") curlPlayer previous ;;
		"repeatStatus") curlPlayer repeatStatus ;;
		"toggleLikeCurrent") curlPlayer toggleLikeCurrent ;;
		*)
			echo \033[91mUnknown\033[0m
			;;
	esac
}

previewCommand() {
	echo "Playing"
}
